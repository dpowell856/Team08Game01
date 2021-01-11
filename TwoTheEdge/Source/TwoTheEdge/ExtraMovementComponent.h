// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtraMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWOTHEEDGE_API UExtraMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExtraMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	class UCharacterMovementComponent* BaseMovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashPower = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashDelay = 5.f;

	/** Requests the player to sprint */
	void Sprint();

	/** Requests the player to walk */
	void Walk();

	UFUNCTION(Server, Reliable)
    void ChangeWalkSpeed(float NewSpeed);

	/** Server side dash logic */
	UFUNCTION(Server, Reliable)
	void ForwardDash();

private:
	float MaxWalkSpeed;
	class ATwoTheEdgeCharacter* Character;
	FTimerHandle DashDelayHandle;
	bool bSprinting = false;
	bool bDashing;
};
