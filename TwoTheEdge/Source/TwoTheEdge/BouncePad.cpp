// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "BouncePad.h"
#include "Components/SphereComponent.h"
#include "TwoTheEdgeCharacter.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

	CollisionSphere->SetSphereRadius(50.f);

	CollisionSphere->SetCollisionProfileName("Trigger");

	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad::OnOverLapBegin);

}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABouncePad::OnOverLapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATwoTheEdgeCharacter::StaticClass()))
	{
		ATwoTheEdgeCharacter* Character = Cast<ATwoTheEdgeCharacter>(OtherActor);
		Character->LaunchCharacter(this->LaunchVelocity,false,false);
	}
}

