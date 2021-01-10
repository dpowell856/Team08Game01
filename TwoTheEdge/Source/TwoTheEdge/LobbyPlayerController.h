// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWOTHEEDGE_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	/** If the client is the host, the game will start */
	UFUNCTION(BlueprintCallable)
	void StartGame();

	/** Returns the number of connected players */
	UFUNCTION(BlueprintCallable)
	int32 GetPlayersConnected() const;

	/** Returns the current player to the main menu */
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu() const;
};
