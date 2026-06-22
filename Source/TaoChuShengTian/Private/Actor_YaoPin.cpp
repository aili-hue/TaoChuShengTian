// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_YaoPin.h"
#include"Components/StaticMeshComponent.h"
#include "Interface/My_Interface.h"
#include "JueSe/My_Character.h"
#include "HP/HP_Component.h"

// Sets default values
AActor_YaoPin::AActor_YaoPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(StaticMeshComponent);
}

void AActor_YaoPin::ZhiXing_Implementation()
{
	if (AMy_Character* Character = Cast<AMy_Character>(GetOwner()))
	{
		if(Character->HPComponent)
		{
			if(Character->HPComponent->AddHP(ZengJia_HP))
			{
				Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("ÑªÁ¿ÒÑÂú"));
			}
		}
	}
}

// Called when the game starts or when spawned
void AActor_YaoPin::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActor_YaoPin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
