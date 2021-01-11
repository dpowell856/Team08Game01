// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "Pickup.h"
#include "TwoTheEdgeCharacter.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnOverlap(AActor* Actor)
{
	if (bDestroyPending)
		return;
	
	// Is Character.
	if (Actor->IsA(ATwoTheEdgeCharacter::StaticClass()))
	{
		ATwoTheEdgeCharacter* Character = Cast<ATwoTheEdgeCharacter>(Actor);

		Pickup(Character);
	}
}

void APickup::Pickup(ATwoTheEdgeCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("%s picked up"), *GetName());
	bDestroyPending = true;

	// Calls Blueprint method.
	OnPickup(Character);
}

