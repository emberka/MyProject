// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpItem.h"
#include "Components/SphereComponent.h"


ASPowerUpItem::ASPowerUpItem()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}


void ASPowerUpItem::Interact_Implementation(APawn* InstigatorPawn)
{
	//Implement specifically for derived classes
}


void ASPowerUpItem::ShowPowerUp()
{
	SetPowerUpState(true);
}


void ASPowerUpItem::Cooldown()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_Reactivate, this, &ASPowerUpItem::ShowPowerUp, RespawnTime);
}

void ASPowerUpItem::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}