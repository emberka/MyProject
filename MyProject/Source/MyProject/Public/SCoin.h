// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpItem.h"
#include "SPlayerState.h"
#include "SCoin.generated.h"

class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API ASCoin : public ASPowerUpItem
{
	GENERATED_BODY()

protected:

	float Amount;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASCoin();
};