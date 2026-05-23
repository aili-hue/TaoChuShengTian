// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "My_WuQi_Actor.generated.h"

UCLASS()
class TAOCHUSHENGTIAN_API AMy_WuQi_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMy_WuQi_Actor();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent>StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent>CapsuleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
