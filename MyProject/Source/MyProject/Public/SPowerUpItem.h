// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerUpItem.generated.h"


class USphereComponent;


UCLASS()
class MYPROJECT_API ASPowerUpItem : public AActor, public ISGameplayInterface

{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "PowerUp")
		float RespawnTime;

	FTimerHandle TimerHandle_Reactivate;

	UFUNCTION()
	void ShowPowerUp();

	void Cooldown();

	void SetPowerUpState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SphereComp;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:

	ASPowerUpItem();

};