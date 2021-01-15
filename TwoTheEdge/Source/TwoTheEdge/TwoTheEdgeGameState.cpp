// 2 The Edge - Team 8: Liam Hall, Dan Powell, Louis Mills, Mo Patel, Ethan Gangotra, Hencraft, keasibanda


#include "TwoTheEdgeGameState.h"
#include "TwoTheEdgePlayerState.h"

void ATwoTheEdgeGameState::BeginPlayDelayed()
{
	for (APlayerState* PlayerState : PlayerArray)
	{
		ATwoTheEdgePlayerState* CastedPlayerState = Cast<ATwoTheEdgePlayerState>(PlayerState);
		SetPlayerColour(CastedPlayerState);
	}
}

void ATwoTheEdgeGameState::SetPlayerColour(ATwoTheEdgePlayerState* PlayerState)
{
	NetworkCheats->AssignPlayerColours(PlayerState, NextColour);

	NextColour++;
	if (NextColour >= 4)
		NextColour = 0;
}
