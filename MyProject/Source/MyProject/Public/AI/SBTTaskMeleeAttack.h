// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTaskMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USBTTaskMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	bool bDamageActor;

	UFUNCTION()
	void MeleeAttack(AActor* DamageCauser, AActor* TargetActor);

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

public:
	
};
