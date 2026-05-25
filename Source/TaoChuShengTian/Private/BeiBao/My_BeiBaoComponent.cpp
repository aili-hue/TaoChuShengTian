// Fill out your copyright notice in the Description page of Project Settings.


#include "BeiBao/My_BeiBaoComponent.h"
#include "MyPrimaryDataAsset.h"

// Sets default values for this component's properties
UMy_BeiBaoComponent::UMy_BeiBaoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UMy_BeiBaoComponent::addWuPin(UMyPrimaryDataAsset* ItemToAdd)
{
	if(ItemToAdd)
	{
		//拾取物品ID名称
		FName WuPinID = ItemToAdd->ID;
		//拾取物品的数量
		int32 ShuLiang = ItemToAdd->ShuLiang;

		if (ShuLiang == 0)return;

		if (!WuPinShuLiang.Contains(WuPinID))
		{
			WuPinShuLiang.Add(WuPinID, ShuLiang);
		}
		else
		{
			WuPinShuLiang[WuPinID] += ShuLiang;
		}
	}
}


// Called when the game starts
void UMy_BeiBaoComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


