// Fill out your copyright notice in the Description page of Project Settings.


#include "HP/HP_Component.h"

// Sets default values for this component's properties
UHP_Component::UHP_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHP_Component::AddHP(float DeltaHP)
{
	HP += DeltaHP;
}

void UHP_Component::DiaoHP(float DeltaHP)
{
	HP -= DeltaHP;
	if(HP<0.f)
	{
		HP = 0.f;
	}
}

float UHP_Component::GetHP()
{
	return HP;
}


void UHP_Component::BeginPlay()
{
	Super::BeginPlay();
}
