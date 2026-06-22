// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"

#include"MyPrimaryDataAsset.h"

#include "Interface/My_Interface.h"


#include "My_Character.generated.h"

//角色拾取委托声明
DECLARE_MULTICAST_DELEGATE(FShiQuWeiTuo);
//打开手电筒
DECLARE_DELEGATE_OneParam(FDaiKai, bool);


class UMyPrimaryDataAsset;

UCLASS()
class TAOCHUSHENGTIAN_API AMy_Character : public ACharacter, public IMy_Interface
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
	bool bShiFouWanCheng = false;
	bool bShiFouWanCheng_QieHuan = true;

	bool bShiFouKeYiGongJi = true;

	//定时器句柄
	FTimerHandle MyShiJiaoTimerHandle;
	//定时器函数
	void ShiJiaoDingShiQi();
	//平滑视角函数
	void ShiJiaoQingHua();
	bool bShiFouGuoJin = false;
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
	UPROPERTY(EditAnywhere, Category = "输入映射|打开关闭背包")
	TObjectPtr<UInputAction>IA_Tab;
	UPROPERTY(EditAnywhere, Category = "输入映射|蹲下")
	TObjectPtr<UInputAction>IA_Dun;
	UPROPERTY(EditAnywhere, Category = "输入映射|清空手上物品")
	TObjectPtr<UInputAction>IA_Q;

	UPROPERTY(EditAnywhere, Category = "输入映射|打开手电筒")
	TObjectPtr<UInputAction>IA_F;
//角色映射调用函数

	void MoveInput(const FInputActionValue&PlayInput);
	void MoveInput_WanCheng(const FInputActionValue&PlayInput);

	void ShuBiao_YiDongInput(const FInputActionValue& PlayInput);
	void JumpInput(const FInputActionValue& PlayInput);
	void ShiftInput(const FInputActionValue& PlayInput);

	void ShiQuInput(const FInputActionValue& PlayInput);
	void GongtjiInput(const FInputActionValue& PlayInput);
	void BeiBaoInPut(const FInputActionValue& PlayInput);
	void DunXiaInPut(const FInputActionValue& PlayInput);
	void QingKongShouShangWuPin(const FInputActionValue& PlayInput);

	void FDaiKaiShouDianTong(const FInputActionValue& PlayInput);

//角色拾取委托

	FShiQuWeiTuo ShiQuWeiTuo;
//角色触发拾取委托函数
	bool ChuLiShiQu(AActor* WuPin, UMyPrimaryDataAsset* WuPinShuJu);
//角色是否拥有武器|近战

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "是否持有近战武器")
	bool bChiYouJinZhanWuQi = false;

//动画蒙太奇数组

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "近战蒙太奇")
	TArray<TObjectPtr<UAnimMontage>>GongJiMontage;
	int32 DongHuaShu = -1;
	UFUNCTION(BlueprintCallable, Category = "获取近战蒙太奇")
	UAnimMontage* QieHuan();
	bool bShiFouJiXuGongJi = true;
//攻击函数
	UFUNCTION(BlueprintImplementableEvent, Category = "攻击")
	void GongJiIpute();
	//武器碰撞标志
	bool bKaiQIPengZhuang = false;
	//是否已经持有近战武器
	bool bYiJingChiYouJinZhanWuQi = false;
	//关闭近战武器碰撞函数
	UFUNCTION(BlueprintCallable, Category = "关闭武器碰撞")
	void GuangBiPengZhuang();

	//背包组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "背包组件")
	TObjectPtr<class UMy_BeiBaoComponent>BeiBaoComponent;

	UFUNCTION(BlueprintImplementableEvent, Category = "打开背包")
	void DaKaiBeiBao();
	UFUNCTION(BlueprintImplementableEvent, Category = "关闭背包")
	void GuanBiBeiBao();

	bool bKaiQi_BeiBao = false;
	//蹲下最大移动速度
	float DunMax = 200.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "是否蹲下")
	bool bShiFouDun = false;
	//角色血量组件

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "血量组件")
	TObjectPtr<class UHP_Component> HPComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "耐力值")
	float Nall = 1.0f;
	UFUNCTION(BlueprintCallable, Category = "获取耐力数值")
	float GetNallllllll() { return Nall; };
	UFUNCTION(BlueprintImplementableEvent, Category = "获取耐力数值")
	void GetNa();

	void HuiFuTiLi();
	void ZengJiaTiLi();
	FTimerHandle TimerHandleDiLi;
	//移动状态
	bool bShiFouJiaSu = false;

    //物品数据
	UFUNCTION(BlueprintCallable, Category = "物品数据")
	void HuoQuShuJv(UMyPrimaryDataAsset* WuPinShuJv);
	void ShuChengWupin(UMyPrimaryDataAsset* WuPinShuJv);
	bool ShiFouXiaoHui = false;
	bool bShiFouKeYi_Tab = true;
	//打开手电筒委托
	FDaiKai DaiKai;
	void DaKaiShoDianTong();
	//是否开灯
	bool bShiFouKaiQiShouDian = false;
	//是否拥有手电筒
	UPROPERTY(BlueprintReadOnly, Category = "是否拥有手电筒")
	bool bShiFouYongYou = false;
	//血量更新
	UFUNCTION(BlueprintImplementableEvent, Category = "血量更新")
	void XueLianngGennngXin();

private:

//角色移动组件

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent>CharacterMovementComponent;

//角色移动速度

	float ChuShiYiDongSuDong = 230.f;
	float MaxYiDongSuDong = 500.f;

	void ShiftInput_Ting();


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

	void SteMoveMent(float MaxSuDu);
	float GetMoveMent();
};
