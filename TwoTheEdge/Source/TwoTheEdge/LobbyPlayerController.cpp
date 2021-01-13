// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "LobbyPlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerController::StartGame()
{
    // If this client is the Host.
    if (GetWorld()->GetGameState()->HasAuthority())
    {
        // Tells the server to change to the arena map.
        GetWorld()->ServerTravel(TEXT("Map3"), false, false);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("Only the Host can start the game!"));
    }
}

int32 ALobbyPlayerController::GetPlayersConnected() const
{
    return GetWorld()->GetGameState()->PlayerArray.Num();
}

void ALobbyPlayerController::LoadMainMenu() const
{
    // Tells the client to change to the main menu map.
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"), true);
}