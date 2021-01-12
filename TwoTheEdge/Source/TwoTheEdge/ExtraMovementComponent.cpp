// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "ExtraMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TwoTheEdgeCharacter.h"
#include "TwoTheEdgePlayerState.h"

// Sets default values for this component's properties
UExtraMovementComponent::UExtraMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExtraMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Character = Cast<ATwoTheEdgeCharacter>(GetOwner());
	BaseMovementComponent = Character->GetCharacterMovement();
	
	MaxWalkSpeed = BaseMovementComponent->MaxWalkSpeed;
}


// Called every frame
void UExtraMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bSprinting)
	{
		ATwoTheEdgePlayerState* PlayerState = Cast<ATwoTheEdgePlayerState>(Character->GetPlayerState());

		// If stamina depleted, force walk.
		PlayerState->Stamina -= DeltaTime;
		if (PlayerState->Stamina <= 0.f)
		{
			PlayerState->Stamina = 0.f;
			Walk();
		}
	}
}

void UExtraMovementComponent::Sprint()
{
	if (bSprinting)
		return;

	ATwoTheEdgePlayerState* PlayerState = Cast<ATwoTheEdgePlayerState>(Character->GetPlayerState());
	if (PlayerState->Stamina <= 0.f)
		return;
	
	ChangeWalkSpeed(SprintSpeed);
	bSprinting = true;
}

void UExtraMovementComponent::Walk()
{
	if (!bSprinting)
		return;
	
	ChangeWalkSpeed(MaxWalkSpeed);
	bSprinting = false;
}

void UExtraMovementComponent::ChangeWalkSpeed_Implementation(float NewSpeed)
{
	BaseMovementComponent->MaxWalkSpeed = NewSpeed;
}

void UExtraMovementComponent::ForwardDash_Implementation()
{
	// On cooldown.
	if (GetWorld()->GetTimerManager().IsTimerActive(DashDelayHandle))
		return;

	const FVector LaunchVelocity = Character->GetMesh()->GetRightVector() * DashPower;
	Character->LaunchCharacter(LaunchVelocity, false, false);
	
	// Adds a delay.
	GetWorld()->GetTimerManager().SetTimer(DashDelayHandle, DashDelay, false, -1);
}

