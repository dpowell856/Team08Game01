// Copyright Epic Games, Inc. All Rights Reserved.

#include "TwoTheEdgeGameMode.h"


#include "NetworkCheats.h"
#include "TwoTheEdgePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATwoTheEdgeGameMode::ATwoTheEdgeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATwoTheEdgeGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	UE_LOG(LogTemp, Warning, TEXT("Logged in"));

	/*FTimerHandle PlayerColourHandle;
	FTimerDelegate PlayerColourDelegate;
	
	PlayerColourDelegate.BindUFunction(this, FName("DoStuff"), NewPlayer);
	
	GetWorld()->GetTimerManager().SetTimer(PlayerColourHandle, PlayerColourDelegate, 10.f, false);
	*/
}