// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Activate(float AdditionalVelocity, float AdditionalDamage, float AdditionalRange)
{
	Damage += AdditionalDamage;
	ProjectileMesh->SetPhysicsLinearVelocity(GetActorForwardVector() * (Velocity + AdditionalVelocity));

	FTimerHandle LifetimeHandle;
	GetWorld()->GetTimerManager().SetTimer(LifetimeHandle, this, &ABullet::OnLifetimeExceeded, Lifetime);
}

int ABullet::GetNetMode()
{
	UE_LOG(LogTemp, Warning, TEXT("LS: %d"), NM_ListenServer);
	UE_LOG(LogTemp, Warning, TEXT("CL: %d"), NM_Client);

	return GEngine->GetNetMode(GetWorld());
}

