// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AI_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UAI_Interface : public UInterface
{
	GENERATED_BODY()
};

class TAOCHUSHENGTIAN_API IAI_Interface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void YunXing(AActor* WanJia);
};
