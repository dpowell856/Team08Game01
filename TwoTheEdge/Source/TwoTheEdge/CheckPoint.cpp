// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "CheckPoint.h"
#include "Components/BoxComponent.h"
#include "TwoTheEdgeCharacter.h"
#include "TwoTheEdgePlayerState.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	CollisionBox->SetCollisionProfileName("Trigger");

	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverLapBegin);

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint::OnOverLapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATwoTheEdgeCharacter::StaticClass()))
	{
		ATwoTheEdgeCharacter* Character = Cast<ATwoTheEdgeCharacter>(OtherActor);
		ATwoTheEdgePlayerState* PlayerState = Cast<ATwoTheEdgePlayerState>(Character->GetPlayerState());
		// PlayerState for whatever reason hasn't loaded yet.
		if (!PlayerState)
			return;
		
		PlayerState->SetLastCheckpoint(GetActorTransform());
	}
}

