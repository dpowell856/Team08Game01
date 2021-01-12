// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncePad.generated.h"

UCLASS()
class TWOTHEEDGE_API ABouncePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	UFUNCTION()
		void OnOverLapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector LaunchVelocity;

};
