// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SThornsEffect.generated.h"

class USAttributeComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT_API USThornsEffect : public USActionEffect
{
	GENERATED_BODY()

public:

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	UFUNCTION()
	void PeriodicEffect(AActor* InstigatorActor, USAttributeComponent* OwningComp, float Health, float Delta);

	USThornsEffect();
	
};
