// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/My_Interface.h"

#include "My_WuQi_Actor.generated.h"

UCLASS()
class TAOCHUSHENGTIAN_API AMy_WuQi_Actor : public AActor,public IMy_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMy_WuQi_Actor();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent>StaticMeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UCapsuleComponent>CapsuleComponent;

	//…Ë÷√≈ˆ◊≤

	bool bIsPengZhuang = false;

	void SetStaticMeshPengZhung(bool KaiGUan);

	//»ı÷∏’Î∞Û∂®
	UPROPERTY()
	TWeakObjectPtr<class AMy_Character>MyCharacterRuoZhiZhen;

	virtual void ZhiXing_Implementation()override;
	virtual void GuangBiPengZhuangVeiTuo_Implementation()override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

};
