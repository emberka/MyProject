// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	Cost = 10.0;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensure(AttributeComp) && !AttributeComp->IsMaxHealth())
		{
			APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
			ASPlayerState* PS = Cast<ASPlayerState>(PC->PlayerState);

			if (PS)
			{
				if (PS->GetNumCredits() >= Cost)
				{
					if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()) && PS->ApplyCreditsChange(this, -Cost))
					{
						Cooldown();
					}
				}

			}

		}
	}
}

