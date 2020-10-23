// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
	Credits = 0.0;
}

bool ASPlayerState::ApplyCreditsChange(AActor* InstigatorActor, float Delta)
{
	float OldCredits = Credits;

	Credits = Credits + Delta;

	float ActualDelta = Credits - OldCredits;

	return ActualDelta != 0;
}

float ASPlayerState::GetNumCredits() const
{
	return Credits;
}
