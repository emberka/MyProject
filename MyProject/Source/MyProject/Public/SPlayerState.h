// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(Replicated)
	float Credits;
	
public:

	UFUNCTION(BlueprintCallable)
		bool ApplyCreditsChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable)
		float GetNumCredits() const;

	ASPlayerState();
};
