// Fill out your copyright notice in the Description page of Project Settings.


#include "door/Actor_door.h"
#include"Components/StaticMeshComponent.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include "JueSe/My_Character.h"

AActor_door::AActor_door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Static_door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("door"));
	SetRootComponent(Static_door);
	Static_door->SetSimulatePhysics(false);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	Box->SetupAttachment(Static_door);
}


void AActor_door::ShiFouKaiQiWuLi(bool bShiFouKaiQi)
{
	if (bShiFouKaiQi && DelegateHandle.IsValid())
	{
		Static_door->SetSimulatePhysics(bShiFouKaiQi);
		DelegateHandle.Reset();
		JueSe->ShiQuWeiTuo.RemoveAll(this);
	}
}

void AActor_door::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!JueSe.IsValid())
	{
	
		AMy_Character* TargetChar = Cast<AMy_Character>(OtherActor);
		if (TargetChar)
		{
			JueSe = TargetChar;
			DelegateHandle = JueSe->ShiQuWeiTuo.AddUObject(this, &ThisClass::ShiFouKaiQiWuLi, true);
		}

	}
}

void AActor_door::OnComponentBeginEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(JueSe.IsValid())
	{
		JueSe->ShiQuWeiTuo.Remove(DelegateHandle);

		DelegateHandle.Reset();
		JueSe = nullptr;
	}
}

void AActor_door::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentBeginEnd);
}

void AActor_door::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(JueSe.IsValid())
	{
		JueSe->ShiQuWeiTuo.RemoveAll(this);
	}
	if (DelegateHandle.IsValid())
	{
		DelegateHandle.Reset();
	}
	JueSe = nullptr;
	Super::EndPlay(EndPlayReason);
}
