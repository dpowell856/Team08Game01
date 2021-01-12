// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "TwoTheEdgePlayerState.h"
#include "Kismet/KismetMathLibrary.h"

void ATwoTheEdgePlayerState::AddDashCharge(const int Amount)
{
    DashCharges = UKismetMathLibrary::Min(DashCharges + Amount, 3);
}

void ATwoTheEdgePlayerState::AddStamina(const float Amount)
{
    Stamina = UKismetMathLibrary::Min(Stamina + Amount, 20.f);
}
