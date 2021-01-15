// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"

#include "EPlayerColour.h"
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

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 PlayerColour;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 LocalPlayerIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform LastCheckpointPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Deaths;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int DashCharges;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ExplosiveGrenades;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int FreezeGrenades;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Finished = -1;

	
	/** Safely add a dash charge */
	UFUNCTION(BlueprintCallable)
	bool AddDashCharge(int Amount = 1);

	/** Safely add a dash charge */
	UFUNCTION(BlueprintCallable)
    bool AddExplosiveGrenades(int Amount = 1);

	/** Safely add a dash charge */
	UFUNCTION(BlueprintCallable)
    bool AddFreezeGrenades(int Amount = 1);

	/** Safely add stamina */
	UFUNCTION(BlueprintCallable)
	bool AddStamina(float Amount);

	UFUNCTION(BlueprintCallable)
	void SetLastCheckpoint(FTransform Checkpoint);

	UFUNCTION(BlueprintCallable)
	FTransform GetLastCheckpoint();

	UFUNCTION()
	void SetPlayerColour(const uint8 Colour) { PlayerColour = Colour; }

	UPROPERTY(BlueprintReadWrite)
	int NextCheckpointNum;

	void UpdateNextCheckpointNum();

};