// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "TwoTheEdgePlayerState.h"
#include "Kismet/KismetMathLibrary.h"

void ATwoTheEdgePlayerState::BeginPlay()
{
    //bUseCustomPlayerNames = 1;
    Super::BeginPlay();
    NextCheckpointNum = 1;
}

bool ATwoTheEdgePlayerState::AddDashCharge(const int Amount)
{
    if (DashCharges >= 3)
        return false;
    
    DashCharges = UKismetMathLibrary::Min(DashCharges + Amount, 3);
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Dash Charges: %d"), DashCharges));
    return true;
}

bool ATwoTheEdgePlayerState::AddExplosiveGrenades(int Amount)
{
    if (ExplosiveGrenades >= 2)
        return false;
    
    ExplosiveGrenades = UKismetMathLibrary::Min(ExplosiveGrenades + Amount, 2);
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Explosive Grenades: %d"), ExplosiveGrenades));
    return true;
}

bool ATwoTheEdgePlayerState::AddFreezeGrenades(int Amount)
{
    if (FreezeGrenades >= 2)
        return false;
    
    FreezeGrenades = UKismetMathLibrary::Min(FreezeGrenades + Amount, 2);
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Freeze Grenades: %d"), FreezeGrenades));
    return true;
}

bool ATwoTheEdgePlayerState::AddStamina(const float Amount)
{
    if (Stamina >= 6.f)
        return false;
    
    Stamina = UKismetMathLibrary::Min(Stamina + Amount, 6.f);
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Stamina: %f"), Stamina));
    return true;
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
