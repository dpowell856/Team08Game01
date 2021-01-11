// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "ExtraMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TwoTheEdgeCharacter.h"

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
}

void UExtraMovementComponent::Sprint()
{
	BaseMovementComponent->MaxWalkSpeed = SprintSpeed;
}

void UExtraMovementComponent::Walk()
{
	BaseMovementComponent->MaxWalkSpeed = MaxWalkSpeed;
}

void UExtraMovementComponent::ForwardDash()
{
	// On cooldown.
	if (GetWorld()->GetTimerManager().IsTimerActive(DashDelayHandle))
		return;

	const FVector LaunchVelocity = Character->GetMesh()->GetRightVector() * DashPower;
	Character->LaunchCharacter(LaunchVelocity, false, false);

	// Adds a delay.
	GetWorld()->GetTimerManager().SetTimer(DashDelayHandle, DashDelay, false, -1);
}

