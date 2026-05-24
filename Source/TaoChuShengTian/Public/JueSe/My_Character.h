// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"

#include"MyPrimaryDataAsset.h"

#include "My_Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FShiQuWeiTuo);

UCLASS()
class TAOCHUSHENGTIAN_API AMy_Character : public ACharacter
{
	GENERATED_BODY()

public:

	AMy_Character();

//角色视角（摄像机，弹簧臂）

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USpringArmComponent>SpringArmComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UCameraComponent>CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "弹簧臂长度")
	float TanHuangBiArmLength = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "弹簧臂位置插槽")
	FName ChaCaoName = TEXT("head");

//角色输入映射

	UPROPERTY(EditAnywhere, Category = "输入映射上下文")
	TObjectPtr<class UInputMappingContext>IMC_Move;

	UPROPERTY(EditAnywhere, Category = "输入映射|移动")
	TObjectPtr<class UInputAction>IA_Move;
	UPROPERTY(EditAnywhere, Category = "输入映射|移动|加速")
	TObjectPtr<UInputAction>IA_Shift;
	UPROPERTY(EditAnywhere, Category = "输入映射|跳跃")
	TObjectPtr<UInputAction>IA_Jump;
	UPROPERTY(EditAnywhere, Category = "输入映射|E拾取")
	TObjectPtr<UInputAction>IA_E;
	UPROPERTY(EditAnywhere, Category = "输入映射|鼠标|视角移动")
	TObjectPtr<UInputAction>IA_ShuBiao_YiDong;
	UPROPERTY(EditAnywhere, Category = "输入映射|鼠标左键|攻击")
	TObjectPtr<UInputAction>IA_GongJi;

//角色映射调用函数

	void MoveInput(const FInputActionValue&PlayInput);
	void ShuBiao_YiDongInput(const FInputActionValue& PlayInput);
	void JumpInput(const FInputActionValue& PlayInput);
	void ShiftInput(const FInputActionValue& PlayInput);
	void ShiQuInput(const FInputActionValue& PlayInput);
	void GongtjiInput(const FInputActionValue& PlayInput);

//角色拾取委托

	FShiQuWeiTuo ShiQuWeiTuo;

	//角色触发拾取委托

	void ChuLiShiQu(AActor* WuPin, UMyPrimaryDataAsset* WuPinShuJu);

//角色持有武器的插槽

	UPROPERTY(EditAnywhere, Category = "角色武器插槽")
	FName WuQiChaCao = TEXT("hand_wuqichacao");
//角色是否拥有武器|近战

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "是否持有近战武器")
	bool bChiYouJinZhanWuQi = false;


private:

//角色移动组件

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent>CharacterMovementComponent;

//角色移动速度

	float ChuShiYiDongSuDong = 230.f;
	float MaxYiDongSuDong = 500.f;

//Actor指针，用来绑定武器

	UPROPERTY()
	TObjectPtr<AActor> WeaponActor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
