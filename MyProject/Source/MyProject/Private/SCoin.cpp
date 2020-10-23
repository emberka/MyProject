// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin.h"
#include "SPlayerState.h"

// Sets default values
ASCoin::ASCoin()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	Amount = 10.0;
}

void ASCoin::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		ASPlayerState* PS = Cast<ASPlayerState>(PC->PlayerState);

		if (PS)
		{
			PS->ApplyCreditsChange(this, Amount);
			Cooldown();
		}

	}
}