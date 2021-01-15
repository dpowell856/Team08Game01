// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "Turret.h"

#include "Bullet.h"
#include "TwoTheEdgeCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Figures out the target through Blueprints since C++ was being mean.
	UpdateTarget();
	UpdateRotation(DeltaTime);
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(ReloadHandle))
		UpdateFiring(DeltaTime);
}

void ATurret::UpdateRotation(float DeltaTime)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(RotationSwitchHandle))
		return;

	FRotator NewRotation = GetActorRotation();

	// Auto rotation
	if (!CurrentTarget || !bTargetPlayer)
	{
		float RotationToAdd = RotationSpeed * DeltaTime;
		if (!bPositiveRotationSign)
			RotationToAdd *= -1.f;
	
		if (bPitch)
			NewRotation.Pitch += RotationToAdd;
		else
			NewRotation.Yaw += RotationToAdd;

		if (!bIgnoreEverythingAndJustDoCircles)
		{
			if (bPitch)
				NewRotation.Pitch = FMath::ClampAngle(NewRotation.Pitch, AngleRange.X, AngleRange.Y);
			else
				NewRotation.Yaw = FMath::ClampAngle(NewRotation.Yaw, AngleRange.X, AngleRange.Y);

			if (NewRotation.Yaw <= AngleRange.X || NewRotation.Yaw >= AngleRange.Y)
			{
				bPositiveRotationSign = !bPositiveRotationSign;
				GetWorld()->GetTimerManager().SetTimer(RotationSwitchHandle, RotationSwitchDelay, false);
			}
		}
	}
	else
	{
		// Target rotation
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTarget->GetActorLocation());

		if (bPitch)
			NewRotation.Pitch = Rotation.Pitch;
		else
			NewRotation.Yaw = Rotation.Yaw;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Rot: %s"), *NewRotation.ToString()));
	SetActorRotation(NewRotation);
}

void ATurret::UpdateFiring(float DeltaTime)
{
	if (CurrentMagSize <= 0)
	{
		StartReload();
	}
}

void ATurret::Fire()
{
	CurrentMagSize--;

	if (BulletActor && BulletSpawnPoint)
	{
		const FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();

		ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletActor, SpawnLocation, SpawnRotation);
		TempBullet->SetOwner(this);
		TempBullet->Activate(BulletVelocity, BulletDamage, BulletMaxRange);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Turret: BulletActor or BulletSpawnPoint not set"));
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fired"));
}

void ATurret::CheckFireCondition()
{
	// If reloading...
	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadHandle))
		return;
	
	Fire();
}

void ATurret::StartReload()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Reloading"));
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &ATurret::FinishReload, ReloadSpeed);
}

void ATurret::FinishReload()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Reloaded"));
	CurrentMagSize = MagazineSize;
}

