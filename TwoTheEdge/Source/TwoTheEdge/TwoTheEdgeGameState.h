// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"

#include "NetworkCheats.h"
#include "GameFramework/GameState.h"
#include "TwoTheEdgeGameState.generated.h"

/**
 * 
 */
UCLASS()
class TWOTHEEDGE_API ATwoTheEdgeGameState : public AGameState
{
	GENERATED_BODY()

	public:
	UPROPERTY(BlueprintReadWrite)
	ANetworkCheats* NetworkCheats;

	uint8 NextColour = 0;
	
	UFUNCTION(BlueprintCallable)
	void BeginPlayDelayed();

	UFUNCTION(BlueprintCallable)
	void SetPlayerColour(ATwoTheEdgePlayerState* PlayerState);
};
