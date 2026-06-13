// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_door.generated.h"

UCLASS()
class TAOCHUSHENGTIAN_API AActor_door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_door();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent>Static_door;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent>Box;

	UPROPERTY()
	TWeakObjectPtr<class AMy_Character>JueSe;
	FDelegateHandle DelegateHandle;
	void ShiFouKaiQiWuLi(bool bShiFouKaiQi);
	float JueSeSuDuQian = 0.f;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentBeginEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	

};
