// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskMeleeAttack.h"
#include "AIController.h"
#include "SGameplayFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"


void  USBTTaskMeleeAttack::MeleeAttack(AActor* DamageCauser, AActor* TargetActor) {
	if (USGameplayFunctionLibrary::ApplyDamage(DamageCauser, TargetActor, 25.0f))
	{
		bDamageActor = true;
	}
}

EBTNodeResult::Type USBTTaskMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (!USAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		AActor* MyActor = Cast<AActor>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		MyPawn->PlayAnimMontage(AttackAnim, 2.0f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = MyPawn;

		bDamageActor = false;
		MeleeAttack(MyActor, TargetActor);

		if (bDamageActor)
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

