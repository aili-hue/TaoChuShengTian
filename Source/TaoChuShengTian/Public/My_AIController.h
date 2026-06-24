// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "My_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TAOCHUSHENGTIAN_API AMy_AIController : public AAIController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ÐÐÎªÊ÷")
	TObjectPtr<UBehaviorTree>BehaviorTree;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
