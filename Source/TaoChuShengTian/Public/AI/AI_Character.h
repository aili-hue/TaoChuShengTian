// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AI_Interface.h"

#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

class UHP_Component;
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

	UFUNCTION(BlueprintCallable, Category = "距离判断")
	void GongJiJvLiPanDuan(AMy_Character* WanJia);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "攻击距离")
	float GongJiJvLi = 120.f;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void YunXing_Implementation(AActor* WanJia)override;
	bool bGongJiZhong = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "攻击")
	void GongJi();

	void GongJiZhiXing();

	UFUNCTION(BlueprintCallable, Category = "关闭碰撞")
	void GuangBiPengZhuangShiJian();
	bool GongJiYiCi = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "伤害数值")
	float ShangHai = 10.f;
	UPROPERTY()
	TObjectPtr<UHP_Component>HP_Component;
	UFUNCTION(BlueprintImplementableEvent, Category = "受击")
	void ShouJiDongHua();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "是否完成受击动画")
	bool bShiFouWanCheng = true;

	UPROPERTY(BlueprintReadWrite, Category = "是否死亡")
	bool bSiWang = false;

	void TingZhiYiDong();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
