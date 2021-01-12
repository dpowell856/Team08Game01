// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda

#pragma once

#include "CoreMinimal.h"

#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerNameHeader.generated.h"

UCLASS()
class TWOTHEEDGE_API APlayerNameHeader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerNameHeader();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRenderComponent;

	AActor* ActorToFollow;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialise(FString PlayerName, FColor Colour, AActor* Follow);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTick();
};
