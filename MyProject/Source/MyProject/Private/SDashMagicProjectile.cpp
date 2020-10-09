// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashMagicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASDashMagicProjectile::ASDashMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASDashMagicProjectile::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASDashMagicProjectile::Explode, 0.2f);

	Super::BeginPlay();
	
}

void ASDashMagicProjectile::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashMagicProjectile::Teleport, 0.2f);
}

void ASDashMagicProjectile::Teleport()
{
	AActor* PlayerTeleport = GetInstigator();

	PlayerTeleport->TeleportTo(GetActorLocation(), PlayerTeleport->GetActorRotation(), false, false);
}

// Called every frame
void ASDashMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

