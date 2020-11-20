// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SSaveGame.h"
#include "Net/UnrealNetwork.h"

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

void ASPlayerState::AddCredits(int32 Delta)
{
	// Avoid user-error of adding a negative amount
	if (!ensure(Delta >= 0.0f))
	{
		return;
	}

	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

float ASPlayerState::GetNumCredits() const
{
	return Credits;
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, Credits);
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}


void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		//Credits = SaveObject->Credits;
		// Makes sure we trigger credits changed event
		AddCredits(SaveObject->Credits);
	}
}
