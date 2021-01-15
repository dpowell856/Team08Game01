// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "NetworkCheats.h"

#include "TwoTheEdgePlayerState.h"

// Sets default values
ANetworkCheats::ANetworkCheats()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkCheats::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkCheats::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetworkCheats::AssignPlayerColours(ATwoTheEdgePlayerState* PlayerState, const uint8& Colour)
{	
	if (!PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState for %s doesn't exist"));
	}
	else
	{
		PlayerState->SetPlayerColour(Colour);

		UE_LOG(LogTemp, Warning, TEXT("Next %d, Current %d"), Colour, PlayerState->PlayerColour);
	}
}
