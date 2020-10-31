// Fill out your copyright notice in the Description page of Project Settings.


#include "SThornsEffect.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"

USThornsEffect::USThornsEffect()
{
	Duration = 0;
	Period = 0;
}

void USThornsEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	USAttributeComponent* AttributeComp;
	AttributeComp = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());

	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &USThornsEffect::PeriodicEffect);
	}
}

void USThornsEffect::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	USAttributeComponent* AttributeComp;
	AttributeComp = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());

	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &USThornsEffect::PeriodicEffect);
	}
}

void USThornsEffect::PeriodicEffect(AActor* InstigatorActor, USAttributeComponent* OwningComp, float Health, float Delta)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	if (InstigatorActor != OwningActor)
	{
		if (Delta < 0.0f)
		{
			int Damage = (float)((int)((Delta + 0.5f) / 5));;

			USGameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, Damage);
		}
	}

}