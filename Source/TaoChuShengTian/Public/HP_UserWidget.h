// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HP_UserWidget.generated.h"


UCLASS()
class TAOCHUSHENGTIAN_API UHP_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ÑªÁ¿×´Ì¬")
	FLinearColor HP_Zhuang_Cool(float HP);
	
};
