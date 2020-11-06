// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpItem.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"


ASPowerUpItem::ASPowerUpItem()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;

	SetReplicates(true);
}


void ASPowerUpItem::Interact_Implementation(APawn* InstigatorPawn)
{
	//Implement specifically for derived classes
}


void ASPowerUpItem::ShowPowerUp()
{
	bConsumed = false;
	OnRep_Consumed();
}


void ASPowerUpItem::Cooldown()
{
	bConsumed = true;
	OnRep_Consumed();
}

void ASPowerUpItem::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUpItem::OnRep_Consumed()
{
	if (bConsumed)
	{
		SetPowerUpState(false);
		GetWorldTimerManager().SetTimer(TimerHandle_Reactivate, this, &ASPowerUpItem::ShowPowerUp, RespawnTime);
	}
	else
	{
		SetPowerUpState(true);
	}
}

void ASPowerUpItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpItem, bConsumed);
}