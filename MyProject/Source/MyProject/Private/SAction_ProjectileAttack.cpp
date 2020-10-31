// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}


void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}


void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass)) {

		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");       //Hand location vector

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FVector CameraLocation = InstigatorCharacter->GetPawnViewLocation();
		FVector EndLocation = CameraLocation + (InstigatorCharacter->GetControlRotation().Vector() * 1500);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FHitResult Hit;
		bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, CameraLocation, EndLocation, ObjectQueryParams, Params);

		if (bBlockingHit)
		{
			EndLocation = Hit.ImpactPoint;
		}

		FRotator NewRotation = FRotationMatrix::MakeFromX(EndLocation - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(NewRotation, HandLocation);

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	}

	StopAction(InstigatorCharacter);
}