// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoTheEdgeCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ExtraMovementComponent.h"
#include "PlayerNameHeader.h"
#include "TwoTheEdgePlayerState.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TwoTheEdgeGameMode.h"

//////////////////////////////////////////////////////////////////////////
// ATwoTheEdgeCharacter

class ATwoTheEdgePlayerState;

ATwoTheEdgeCharacter::ATwoTheEdgeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ATwoTheEdgeCharacter::OnPossessed_Implementation(AController* NewController)
{
	PossessedServer(NewController);
}

//////////////////////////////////////////////////////////////////////////
// Input
void ATwoTheEdgeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATwoTheEdgeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATwoTheEdgeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATwoTheEdgeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATwoTheEdgeCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATwoTheEdgeCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATwoTheEdgeCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATwoTheEdgeCharacter::OnResetVR);

	// Crouch
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATwoTheEdgeCharacter::DoCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATwoTheEdgeCharacter::DoUnCrouch);

	// Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATwoTheEdgeCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATwoTheEdgeCharacter::Walk);

	// Forward dash
	PlayerInputComponent->BindAction("ForwardDash", IE_Pressed, this, &ATwoTheEdgeCharacter::ForwardDash);

	// Respawn
	PlayerInputComponent->BindAction("Respawn", IE_Pressed, this, &ATwoTheEdgeCharacter::Respawn);
}

void ATwoTheEdgeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATwoTheEdgeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATwoTheEdgeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATwoTheEdgeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATwoTheEdgeCharacter::DoCrouch()
{
	Crouch(true);
}

void ATwoTheEdgeCharacter::DoUnCrouch()
{
	UnCrouch(true);
}

void ATwoTheEdgeCharacter::Sprint()
{
	ExtraMovement->Sprint();
	OnSprint(true);
}

void ATwoTheEdgeCharacter::Walk()
{
	ExtraMovement->Walk();
	OnSprint(false);
}

void ATwoTheEdgeCharacter::ForwardDash()
{
	ATwoTheEdgePlayerState* CastedPlayerState = GetPlayerState<ATwoTheEdgePlayerState>();
	
	if (CastedPlayerState->DashCharges > 0)
	{
		if (ExtraMovement->GetDashOnDelay())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Dash on delay"));
			return;
		}
		
		CastedPlayerState->DashCharges--;

		ExtraMovement->ForwardDash();
		
		// Blueprint event.
		OnForwardDash();
	}
}

void ATwoTheEdgeCharacter::Respawn()
{
	// If host
	if (HasAuthority())
	{
		// Shows respawn animation to self and other players.
		RespawnOnHost();
	}
	else
	{
		// Shows respawn animation to other players.
		RespawnOnServer();
		// Shows respawn animation to self.
		RespawnOnClient();
	}
}

void ATwoTheEdgeCharacter::RespawnOnServer_Implementation()
{
	OnRespawn();
}

void ATwoTheEdgeCharacter::RespawnOnClient_Implementation()
{
	OnRespawn();
}

void ATwoTheEdgeCharacter::RespawnOnHost_Implementation()
{
	OnRespawn();
}

void ATwoTheEdgeCharacter::CreatePlayerName_Implementation(APlayerCameraManager* CameraManager)
{
	// Hide the player name text if it's the local player.
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) != this)
	{
		APlayerNameHeader* NameHeader = Cast<APlayerNameHeader>(
            GetWorld()->SpawnActor(PlayerNameClass, &GetTransform()));

		NameHeader->CameraManager = CameraManager;

		// Gets the player name of this pawn's owner.
		APlayerState* ThisPlayerState = GetPlayerState();
		ATwoTheEdgePlayerState* Re = Cast<ATwoTheEdgePlayerState>(ThisPlayerState);

		FString PlayerName;
		if (ThisPlayerState)
		{
			PlayerName = GetPlayerState()->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(Re->PlayerColour));
		}
		else
			PlayerName = "Nameless";
		
		// Caps the name's length.
		PlayerName = PlayerName.Left(15);
		NameHeader->Initialise(PlayerName, FColor::Orange, this);
	}
}

void ATwoTheEdgeCharacter::TeleportOnServer_Implementation(const FVector& DestLocation, const FRotator& DestRotation)
{
	// Movement must be done on server.
	TeleportTo(DestLocation, DestRotation);
}

void ATwoTheEdgeCharacter::RequestGrenadeThrow(const int32& GrenadeType)
{
	ATwoTheEdgePlayerState* CastedPlayerState = GetPlayerState<ATwoTheEdgePlayerState>();

	switch (GrenadeType)
	{
		case 0:
			if (CastedPlayerState->ExplosiveGrenades > 0)
				CastedPlayerState->ExplosiveGrenades--;
			else
				return;
		break;
		case 1:
			if (CastedPlayerState->FreezeGrenades > 0)
				CastedPlayerState->FreezeGrenades--;
			else
				return;
		break;
		default:
			return;
	}
		
	// If host
	if (HasAuthority())
	{
		// Shows respawn animation to self and other players.
		GrenadeThrowServer(GrenadeType);
	}
	else
	{
		// Sending info to server and client works perfectly.
		// The problem is sending the info from the server to other clients.
		GrenadeThrowServer(GrenadeType);
		GrenadeThrowClient(GrenadeType);
	}
}

void ATwoTheEdgeCharacter::GrenadeThrowServer_Implementation(const int32& GrenadeType)
{
	OnGrenadeThrow(GrenadeType);
}

void ATwoTheEdgeCharacter::GrenadeThrowClient_Implementation(const int32& GrenadeType)
{
	OnGrenadeThrow(GrenadeType);
}

void ATwoTheEdgeCharacter::GrenadeThrowNetCast_Implementation(const int32& GrenadeType)
{
	OnGrenadeThrow(GrenadeType);
}

void ATwoTheEdgeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATwoTheEdgeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATwoTheEdgeCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATwoTheEdgeCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATwoTheEdgeCharacter::Jump()
{
	Super::Jump();

	OnJump();
}
