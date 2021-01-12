// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "TwoTheEdgePlayerState.h"
#include "Kismet/KismetMathLibrary.h"

void ATwoTheEdgePlayerState::AddDashCharge(const int Amount)
{
    DashCharges = UKismetMathLibrary::Min(DashCharges + Amount, 3);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Dash Charges: %d"), DashCharges));
}

void ATwoTheEdgePlayerState::AddStamina(const float Amount)
{
    Stamina = UKismetMathLibrary::Min(Stamina + Amount, 20.f);
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Stamina: %f"), Stamina));
}
