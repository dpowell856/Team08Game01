// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "TwoTheEdgePlayerState.h"
#include "Kismet/KismetMathLibrary.h"

void ATwoTheEdgePlayerState::BeginPlay()
{
    //bUseCustomPlayerNames = 1;
    Super::BeginPlay();
    NextCheckpointNum = 1;
}

void ATwoTheEdgePlayerState::AddDashCharge(const int Amount)
{
    DashCharges = UKismetMathLibrary::Min(DashCharges + Amount, 3);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Dash Charges: %d"), DashCharges));
}

void ATwoTheEdgePlayerState::AddExplosiveGrenades(int Amount)
{
    ExplosiveGrenades = UKismetMathLibrary::Min(ExplosiveGrenades + Amount, 2);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Explosive Grenades: %d"), ExplosiveGrenades));
}

void ATwoTheEdgePlayerState::AddFreezeGrenades(int Amount)
{
    FreezeGrenades = UKismetMathLibrary::Min(FreezeGrenades + Amount, 2);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Freeze Grenades: %d"), FreezeGrenades));
}

void ATwoTheEdgePlayerState::AddStamina(const float Amount)
{
    Stamina = UKismetMathLibrary::Min(Stamina + Amount, 20.f);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Stamina: %f"), Stamina));
}

void ATwoTheEdgePlayerState::SetLastCheckpoint(FTransform CheckpointPos)
{
    this->LastCheckpointPos = CheckpointPos;
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Checkpoint set %s"),*LastCheckpointPos.ToString()));
    UpdateNextCheckpointNum();
}

FTransform ATwoTheEdgePlayerState::GetLastCheckpoint()
{
    return this->LastCheckpointPos;
}

void ATwoTheEdgePlayerState::UpdateNextCheckpointNum()
{
    NextCheckpointNum++;
}
