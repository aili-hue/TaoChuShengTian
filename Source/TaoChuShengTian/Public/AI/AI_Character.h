// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AI_Interface.h"

#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

class UBoxComponent;


UCLASS()
class TAOCHUSHENGTIAN_API AAI_Character : public ACharacter, public IAI_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UBoxComponent>BoxComponent;

	UFUNCTION(BlueprintCallable, Category = "¾àÀëÅÐ¶Ï")
	void GongJiJvLiPanDuan(AMy_Character* WanJia);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "¹¥»÷¾àÀë")
	float GongJiJvLi = 120.f;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void YunXing_Implementation(AActor* WanJia)override;
	bool bGongJiZhong = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "¹¥»÷")
	void GongJi();

	void GongJiZhiXing();

	UFUNCTION(BlueprintCallable, Category = "¹Ø±ÕÅö×²")
	void GuangBiPengZhuangShiJian();
	bool GongJiYiCi = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
