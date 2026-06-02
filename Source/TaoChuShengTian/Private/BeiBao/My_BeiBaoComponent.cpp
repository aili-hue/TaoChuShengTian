// Fill out your copyright notice in the Description page of Project Settings.


#include "BeiBao/My_BeiBaoComponent.h"
#include "MyPrimaryDataAsset.h"
#include "JueSe/My_Character.h"
#include"Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UMy_BeiBaoComponent::UMy_BeiBaoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool UMy_BeiBaoComponent::addWuPin(UMyPrimaryDataAsset* ItemToAdd)
{

	if (!ItemToAdd || ItemToAdd->ID.IsNone() || ItemToAdd->ShuLiang <= 0)return false;
	//拾取物品ID名称
	FName WuPinID = ItemToAdd->ID;
	//拾取物品的数量
	int32 ShuLiang = ItemToAdd->ShuLiang;
	UTexture2D* Texture2D = ItemToAdd->Texture2D;
	int32 WuPinShuLiang = 0;
	if (!WuPinShuJv.Contains(WuPinID))
	{
		WuPinShuLiang = ShuLiang;
		WuPinShuJv.Emplace(WuPinID, WuPinShuLiang);
		WuPinZiChanDiTu.Emplace(WuPinID, ItemToAdd);
	}
	else
	{
		WuPinShuLiang = WuPinShuJv[WuPinID] + ShuLiang;
		WuPinShuJv[WuPinID] = WuPinShuLiang;
	}
	WuPinXinXi(WuPinID, WuPinShuLiang, Texture2D);

	return true;
}

int32 UMy_BeiBaoComponent::GetBeiBaoWuPinShuLiang(FName WuPinID)
{
	//const只读去WuPinShuJv.Find(WuPinID)的值
	if (const int32* WuPinShuLiang = WuPinShuJv.Find(WuPinID))
	{
		return *WuPinShuLiang;
	}
	return 0;
}

TArray<UMyPrimaryDataAsset*> UMy_BeiBaoComponent::ShiQUWuPinShuJv()
{
	TArray<UMyPrimaryDataAsset*>JieGuo;
	//数组预留WuPinZiChanDiTu的位数
	JieGuo.Reserve(WuPinZiChanDiTu.Num());
	//遍历tmap并将值写入数组中
	for(const auto& WuPinZiChanDiT: WuPinZiChanDiTu)
	{
	}
	return JieGuo;
}

void UMy_BeiBaoComponent::WuPinXinXi(FName WuPinID, int32 WuPinShuLiang, UTexture2D* TuXiang)
{
	GengXin.Broadcast(WuPinID, WuPinShuLiang, TuXiang);
}

// Called when the game starts
void UMy_BeiBaoComponent::BeginPlay()
{
	Super::BeginPlay();

}


