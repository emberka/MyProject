// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp && !AttributeComp->IsMaxHealth())
		{
			AttributeComp->ApplyHealthChange(15.0f);
			SetActorEnableCollision(false);
			SetActorHiddenInGame(true); 
			
			GetWorldTimerManager().SetTimer(TimerHandle_Reactivate, this, &ASHealthPotion::Reactivate, 10.0f);
		}
	}
}

void ASHealthPotion::Reactivate()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

