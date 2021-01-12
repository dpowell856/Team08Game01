// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "PlayerNameHeader.h"

// Sets default values
APlayerNameHeader::APlayerNameHeader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerNameHeader::BeginPlay()
{
	Super::BeginPlay();
	
	TextRenderComponent->SetText(TEXT(""));
}

// Called every frame
void APlayerNameHeader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorToFollow)
		SetActorLocation(ActorToFollow->GetActorLocation());

	OnTick();
}

void APlayerNameHeader::Initialise(FString PlayerName, FColor Colour, AActor* Follow)
{
	TextRenderComponent->SetTextRenderColor(Colour);
	TextRenderComponent->SetText(PlayerName);
	ActorToFollow = Follow;
}

