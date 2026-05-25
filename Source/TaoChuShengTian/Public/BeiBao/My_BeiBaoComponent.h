// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "My_BeiBaoComponent.generated.h"

class UMyPrimaryDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAOCHUSHENGTIAN_API UMy_BeiBaoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMy_BeiBaoComponent();

	UFUNCTION()
	void addWuPin(UMyPrimaryDataAsset* ItemToAdd);

private:
	TMap<FName, int32>WuPinShuLiang;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
