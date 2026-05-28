// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "My_BeiBaoComponent.generated.h"

class UMyPrimaryDataAsset;

//更新背包
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGengXin, FName, ItemID, int32, NewCount,UTexture2D*,TuXiang);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAOCHUSHENGTIAN_API UMy_BeiBaoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMy_BeiBaoComponent();

	void addWuPin(UMyPrimaryDataAsset* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "获取背包中物品数量")
	int32 GetBeiBaoWuPinShuLiang(FName WuPinID);

	UFUNCTION(BlueprintCallable)
	TArray<UMyPrimaryDataAsset*> ShiQUWuPinShuJv();

	void WuPinXinXi(FName WuPinID, int32 WuPinShuLiang, UTexture2D* TuXiang);
	//背包更新
	UPROPERTY(BlueprintAssignable, Category = "背包更新数据")
	FGengXin GengXin;
private:
	UPROPERTY()
	TMap<FName, int32> WuPinShuJv;
	UPROPERTY()
	TMap<FName, TObjectPtr<UMyPrimaryDataAsset>> WuPinZiChanDiTu;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
