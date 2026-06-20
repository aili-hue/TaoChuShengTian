// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Actor_WuPin.h"

#include "My_GameModeBase.generated.h"


UCLASS()
class TAOCHUSHENGTIAN_API AMy_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = "所有报道的Actor物品")
	TArray<TObjectPtr<class AActor_WuPin>>WuPinActor;
	UPROPERTY(EditAnywhere, Category = "数据")
	TArray<TObjectPtr<class UMyPrimaryDataAsset>>SuiJi_ShuJv;
	//随机物品索引
	int32 SuiJi_ShuJv_SuoYin = 0;

	void MyXingWuPin(AActor_WuPin* WuPin);
};
