// Fill out your copyright notice in the Description page of Project Settings.


#include "HP/HP_Component.h"
#include "JueSe/My_Character.h"

// Sets default values for this component's properties
UHP_Component::UHP_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UHP_Component::AddHP(float DeltaHP)
{
	if (HP >= 100.f)return false;
	float OldHP = HP;
	HP = FMath::Clamp(HP += DeltaHP, 0.f, 100.f);
	if (HP > OldHP)
	{
		if (AMy_Character* Character = Cast<AMy_Character>(GetOwner()))
		{
			Character->XueLianngGennngXin();
			return true;
		}
	}
	return false;
}

void UHP_Component::DiaoHP(float DeltaHP)
{
	float OldHP = HP;
	HP = FMath::Clamp(HP -= DeltaHP, 0.f, 100.f);
	if(HP < OldHP)
	{
		if (AMy_Character* Character = Cast<AMy_Character>(GetOwner()))
		{
			Character->XueLianngGennngXin();
		}
	}

	if(HP<=0.f)
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
