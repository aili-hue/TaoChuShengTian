// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HP_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAOCHUSHENGTIAN_API UHP_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHP_Component();


//血量逻辑	
	UFUNCTION(BlueprintCallable, Category="加血")
	void AddHP(float DeltaHP);

	UFUNCTION(BlueprintCallable, Category = "掉血")
	void DiaoHP(float DeltaHP);

	UFUNCTION(BlueprintCallable, Category = "获取血量")
	float GetHP();
private:

	float HP = 100.f; //初始血量

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	

		
};
