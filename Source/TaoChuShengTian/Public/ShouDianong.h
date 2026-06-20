// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShouDianong.generated.h"

class UStaticMeshComponent;
class USpotLightComponent;

UCLASS()
class TAOCHUSHENGTIAN_API AShouDianong : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShouDianong();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>StaticMeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USpotLightComponent>SpotLightComponent;

	UPROPERTY()
	TWeakObjectPtr<class AMy_Character>Character;
	void BindWeiTuo();
	void ShouDianTongKaiGuan(bool bShiFouKaiQi);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	

};
