// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TWOTHEEDGE_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	float BulletVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	int BulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	int BulletMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	int MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	float ReloadSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	UClass* BulletActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Bullets)
	USceneComponent* BulletSpawnPoint;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	float RotationSpeed;

	/** Ignores all the angle limits and stuff and just keeps on spinning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bIgnoreEverythingAndJustDoCircles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	float RotationSwitchDelay;

	/** False = Yaw, True = Pitch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	FVector2D AngleRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)
	bool bTargetPlayer;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTarget();

private:
	FTimerHandle FireRateHandle;
	FTimerHandle ReloadHandle;
	FTimerHandle RotationSwitchHandle;

	int CurrentMagSize;
	bool bPositiveRotationSign;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Rotation, meta = (AllowPrivateAccess = "true"))
	AActor* CurrentTarget;
	
	void UpdateRotation(float DeltaTime);
	void UpdateFiring(float DeltaTime);
	void Fire();
	void CheckFireCondition();
	void StartReload();
	void FinishReload();
};
