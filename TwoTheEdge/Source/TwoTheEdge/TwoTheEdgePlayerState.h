// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TwoTheEdgePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TWOTHEEDGE_API ATwoTheEdgePlayerState : public APlayerState
{
	GENERATED_BODY()

	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* LastCheckpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Deaths;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int DashCharges;

	/** Safely add a dash charge */
	UFUNCTION(BlueprintCallable)
	void AddDashCharge(int Amount = 1);
	
};
