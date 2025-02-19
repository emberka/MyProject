// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpItem.h"
#include "SPlayerState.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API ASHealthPotion : public ASPowerUpItem
{
	GENERATED_BODY()

protected:

	float Cost;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASHealthPotion();
};

