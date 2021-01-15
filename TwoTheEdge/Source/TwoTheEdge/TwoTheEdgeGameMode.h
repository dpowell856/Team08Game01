// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EPlayerColour.h"
#include "GameFramework/GameMode.h"
#include "TwoTheEdgeGameMode.generated.h"

UCLASS(minimalapi)
class ATwoTheEdgeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATwoTheEdgeGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	uint8 NextPlayerColour = EPlayerColour::Cyan;
};



