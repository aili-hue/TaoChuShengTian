// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_WuPin.generated.h"

UCLASS()
class TAOCHUSHENGTIAN_API AActor_WuPin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_WuPin();
	//静态网格体组件
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent>StaticMeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>StaticMeshGaoGuang;
	//球形碰撞
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USphereComponent>SphereComponent;
	//数据资产
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品数据资产")
	TObjectPtr<class UMyPrimaryDataAsset>WuPinShuJu;

	void FuYuMyShuJv(UMyPrimaryDataAsset* ChuDiShuJv);

	//碰撞函数
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//弱指针绑定
	TWeakObjectPtr<class AMy_Character> ZhiZhenMyCharacter;
	void ChuFaShiQuWeiTuo();
	//随机物品
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "随机物品和物品数据")
	TMap< TObjectPtr<UMyPrimaryDataAsset>, TObjectPtr<UStaticMesh>>WuPin_ShuJv;
	void SuiJi();
	//高光材质
	UPROPERTY(EditAnywhere, Category = "高光材质")
	TObjectPtr<UMaterial> GaoGuangCaiZhi;
private:

	//触发高光
	bool bIsChongDie = false;

	//委托句柄
	FDelegateHandle WeiTuoJvBing;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
