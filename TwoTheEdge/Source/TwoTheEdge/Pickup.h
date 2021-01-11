// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class ATwoTheEdgeCharacter;
UCLASS()
class TWOTHEEDGE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Pickup(ATwoTheEdgeCharacter* Character);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Actor);

	/** Called when the item has been picked up */
	UFUNCTION(BlueprintImplementableEvent)
	void OnPickup(ATwoTheEdgeCharacter* Character);

private:
	bool bDestroyPending;
};
