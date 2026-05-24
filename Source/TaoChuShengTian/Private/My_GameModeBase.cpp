// Fill out your copyright notice in the Description page of Project Settings.


#include "My_GameModeBase.h"
#include "MyPrimaryDataAsset.h"
#include "Actor_WuPin.h"


void AMy_GameModeBase::MyXingWuPin(AActor_WuPin* WuPin)
{
	if (SuiJi_ShuJv.Num() == 0)return;
	if (!WuPin)return;
	//将物品添加到物品数组中
	WuPinActor.Add(WuPin);
	SuiJi_ShuJv_SuoYin = FMath::RandRange(0, SuiJi_ShuJv.Num() - 1);
	UMyPrimaryDataAsset* WuPPinShuJv = SuiJi_ShuJv[SuiJi_ShuJv_SuoYin];

	WuPin->WuPinShuJu = WuPPinShuJv;
}

void AMy_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
