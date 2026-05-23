// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyPrimaryDataAsset.generated.h"

UENUM(BlueprintType)
enum class EMYUELeiXing : uint8
{
	BangQiuGun UMETA(DisplayName = "棒球棍")
};

UCLASS(BlueprintType)
class TAOCHUSHENGTIAN_API UMyPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "身份证")
	FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品类型")
	EMYUELeiXing MYUELeiXing = EMYUELeiXing::BangQiuGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品数量")
	int32 ShuLiang = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品功能")
	TSubclassOf<AActor>CunFangActor;
};
