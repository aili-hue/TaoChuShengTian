// Fill out your copyright notice in the Description page of Project Settings.


#include "JueSe/My_Character.h"
#include"GameFramework/SpringArmComponent.h"

#include"GameFramework/CharacterMovementComponent.h"

#include"Camera/CameraComponent.h"

#include"InputMappingContext.h"
#include"InputAction.h"

#include"EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"

#include "Actor_WuPin.h"

#include "BeiBao/My_BeiBaoComponent.h"

#include "HP/HP_Component.h"


// Sets default values
AMy_Character::AMy_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetMesh(), ChaCaoName);
	SpringArmComponent->TargetArmLength = TanHuangBiArmLength;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

//角色血量组件
	
	HPComponent=CreateDefaultSubobject<UHP_Component>(TEXT("HPComponent"));

//获取角色移动组件

	CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;

//背包组件
	BeiBaoComponent = CreateDefaultSubobject<UMy_BeiBaoComponent>(TEXT("BeiBaoComponent"));

}
void AMy_Character::ShiJiaoDingShiQi()
{
	GetWorldTimerManager().ClearTimer(MyShiJiaoTimerHandle);

	
	bShiFouWanCheng_QieHuan = false;

	
	GetWorldTimerManager().SetTimer(MyShiJiaoTimerHandle, this, &ThisClass::ShiJiaoQingHua, 0.01f, true);
}
//设置弹簧臂长度
void AMy_Character::ShiJiaoQingHua()
{
	// 核心逻辑：动态确定目标。有武器目标是 100，没武器目标是 0
	float TargetValue = WeaponActor ? 100.f : 0.f;

	//如果过近就切换第一人称
	if (bShiFouGuoJin && TargetValue != 0.f)TargetValue = 0.f;

	// FInterpTo 会自动计算：从“当前值”到“目标值”的步进
	TanHuangBiArmLength = FMath::FInterpTo(TanHuangBiArmLength, TargetValue, 0.01f, 10.f);
	SpringArmComponent->TargetArmLength = TanHuangBiArmLength;

	// 既然在动，就还没完成
	bShiFouWanCheng_QieHuan = false;

	// 判断是否足够接近
	if (FMath::IsNearlyEqual(TanHuangBiArmLength, TargetValue, 0.1f))
	{
		// 强行对齐，确保数值精确
		TanHuangBiArmLength = TargetValue;
		SpringArmComponent->TargetArmLength = TanHuangBiArmLength;

		GetWorldTimerManager().ClearTimer(MyShiJiaoTimerHandle);
		bShiFouWanCheng_QieHuan = true;
	}
}


//角色移动
void AMy_Character::MoveInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	FVector2D MoveVector2D = PlayInput.Get<FVector2D>();
	FRotator MoveRotator = Controller->GetControlRotation();
	FRotator MoveControlRotator(0.f, MoveRotator.Yaw, 0.f);
	FVector JvZhen_X = FRotationMatrix(MoveControlRotator).GetUnitAxis(EAxis::Y);
	FVector JvZhen_Y = FRotationMatrix(MoveControlRotator).GetUnitAxis(EAxis::X);
	AddMovementInput(JvZhen_X, MoveVector2D.Y);
	AddMovementInput(JvZhen_Y, MoveVector2D.X);

	//加速限制

	if (!bShiFouJiaSu)return;

	if (GetWorldTimerManager().IsTimerActive(TimerHandleDiLi))GetWorldTimerManager().ClearTimer(TimerHandleDiLi);

	Nall -= 0.09f * GetWorld()->GetDeltaSeconds();
	GetNa();

	if (Nall <= 0.f)
	{
		Nall = 0.f;
		bShiFouJiaSu = false;
		CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;
		//回复体力
		HuiFuTiLi();
	}

}

void AMy_Character::MoveInput_WanCheng(const FInputActionValue& PlayInput)
{
	float MoveSuDu = GetMoveMent();
	if (!bShiFouJiaSu && MoveSuDu > ChuShiYiDongSuDong)return;
	HuiFuTiLi();
}

void AMy_Character::HuiFuTiLi()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandleDiLi))return;
	GetWorldTimerManager().SetTimer(TimerHandleDiLi, this, &ThisClass::ZengJiaTiLi, 0.1f, true);
}

void AMy_Character::ZengJiaTiLi()
{
	if(Nall>=1.f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandleDiLi);
		Nall = 1.f;
		return;
	}
	GetNa();
	Nall += 0.2f * GetWorld()->GetDeltaSeconds();
}

void AMy_Character::HuoQuShuJv(UMyPrimaryDataAsset* WuPinShuJv)
{
	if(WuPinShuJv)
	{
		ShuChengWupin(WuPinShuJv);
	}

}

void AMy_Character::ShuChengWupin(UMyPrimaryDataAsset* WuPinShuJv)
{
	if (!WuPinShuJv)return;
	//根据物品数据资产的类型和数量进行相应的处理，比如增加玩家的属性，或者在角色上生成一个新的Actor（比如武器）
	if (WuPinShuJv->CunFangActor)
	{
		//如果角色上已经有了武器，就先销毁原来的武器
		if (WeaponActor)
		{
			WeaponActor->Destroy();
			WeaponActor = nullptr;
		}
		//设置生成Actor参数
		FActorSpawnParameters ShengChengActorCanShu;
		//设置角色为生成Actor的拥有者
		ShengChengActorCanShu.Owner = this;
		//设置角色为生成Actor的触发者
		ShengChengActorCanShu.Instigator = this;
		//生成Actor，并将生成的Actor指针赋值给WeaponActor
		WeaponActor = GetWorld()->SpawnActor<AActor>(WuPinShuJv->CunFangActor, ShengChengActorCanShu);
		UE_LOG(LogTemp, Log, TEXT("成功"));
	}
	//如果生成了武器Actor，就将它绑定到角色的武器插槽上
	if (WeaponActor)
	{
		//将生成的武器Actor绑定到角色的武器插槽上
		WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WuQiChaCao);

		//玩家持有近战武器
		if (WuPinShuJv->MYUELeiXing == EMYUELeiXing::WuQi_JinZhan && !bYiJingChiYouJinZhanWuQi)
		{
			bChiYouJinZhanWuQi = true;

			bYiJingChiYouJinZhanWuQi = !bYiJingChiYouJinZhanWuQi;
			ShiJiaoDingShiQi();
		}

	}
	else
	{
		WeaponActor = nullptr;
	}

}


//鼠标移动视角
void AMy_Character::ShuBiao_YiDongInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	FVector2D ShuBiaoYIDongVector2D = PlayInput.Get<FVector2D>();
	AddControllerYawInput(ShuBiaoYIDongVector2D.X);
	AddControllerPitchInput(ShuBiaoYIDongVector2D.Y);
	
}

void AMy_Character::JumpInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	Jump();
}

//角色加速度
void AMy_Character::ShiftInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	//如果移动速度属于正常移动速度且不属于蹲下，就可以加速
	if (CharacterMovementComponent->MaxWalkSpeed == ChuShiYiDongSuDong && !bShiFouDun && Nall >= 0.3f)
	{
		CharacterMovementComponent->MaxWalkSpeed = MaxYiDongSuDong;
		bShiFouJiaSu = true;
		return;
	}
	if(!bShiFouDun)
	{
		CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;
		HuiFuTiLi();

		bShiFouJiaSu = false;
	}
}
//拾取物品input
void AMy_Character::ShiQuInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	ShiQuWeiTuo.Broadcast();
}

//棒球棍碰撞
void AMy_Character::ChuFaPengZhuangFunc(bool bPengZhuang)
{
	ChuFaPengZhuang.ExecuteIfBound(bPengZhuang);
}

bool AMy_Character::ChuLiShiQu(AActor* WuPin, UMyPrimaryDataAsset* WuPinShuJu)
{
	//先判断物品和物品数据资产是否有效
	if (!WuPin || !WuPinShuJu) return false;
	//将拾取的物品传递给背包组件
	if(!BeiBaoComponent->addWuPin(WuPinShuJu))
	{
		return false;
	}
	ShuChengWupin(WuPinShuJu);
	return true;
}
//切换近战动画
UAnimMontage* AMy_Character::QieHuan()
{
	if (GongJiMontage.Num() == 0)return nullptr;
	//用动画总数来%判断是否为最大值如果为就归零如果不为则正常增加
	DongHuaShu = (DongHuaShu + 1) % GongJiMontage.Num();

	return GongJiMontage[DongHuaShu];
}

void AMy_Character::GuangBiPengZhuang()
{
	//关闭武器碰撞
	bKaiQIPengZhuang = false;
	ChuFaPengZhuangFunc(bKaiQIPengZhuang);
}
void AMy_Character::GongtjiInput(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	//如果角色没有武器，就无法攻击
	if (!WeaponActor)return;
	if (!bShiFouKeYiGongJi)return;
	//如果角色持有近战武器，就触发攻击事件
	if (bChiYouJinZhanWuQi && !bKaiQIPengZhuang && !bShiFouDun)
	{
		//开启武器碰撞
		bKaiQIPengZhuang = true;
		ChuFaPengZhuangFunc(bKaiQIPengZhuang);
		GongJiIpute();
	}
}
//背包input执行函数
void AMy_Character::BeiBaoInPut(const FInputActionValue& PlayInput)
{
	if(!bKaiQi_BeiBao)
	{
		DaKaiBeiBao();
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)PlayerController->SetShowMouseCursor(true);

		bKaiQi_BeiBao = !bKaiQi_BeiBao;
		return;
	}
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)PlayerController->SetShowMouseCursor(false);

	GuanBiBeiBao();
	bKaiQi_BeiBao = !bKaiQi_BeiBao;

}
//蹲下
void AMy_Character::DunXiaInPut(const FInputActionValue& PlayInput)
{

	if (bKaiQi_BeiBao)return;

	bShiFouDun = !bShiFouDun;
	if(bShiFouDun)
	{
		CharacterMovementComponent->MaxWalkSpeed = DunMax;
		bShiFouJiaSu = false;
		HuiFuTiLi();
		return;
	}
	CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;
}
//清空手上物品
void AMy_Character::QingKongShouShangWuPin(const FInputActionValue& PlayInput)
{
	if (bKaiQi_BeiBao)return;

	if (WeaponActor && bShiFouWanCheng_QieHuan)
	{
		WeaponActor->Destroy();
		WeaponActor = nullptr;

		//切换视角
		bChiYouJinZhanWuQi = false;
		bYiJingChiYouJinZhanWuQi = false;
		
		ShiJiaoDingShiQi();
	}
}


void AMy_Character::SteMoveMent(float MaxSuDu)
{
	CharacterMovementComponent->MaxWalkSpeed = MaxSuDu;
}
//角色自身速度
float AMy_Character::GetMoveMent()
{
	float sudu = GetCharacterMovement()->MaxWalkSpeed;
	return sudu;
}

void AMy_Character::ShiftInput_Ting()
{
}

// Called when the game starts or when spawned
void AMy_Character::BeginPlay()
{
	Super::BeginPlay();
//增强输入注册	
	if (APlayerController* WanJiaController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* BenDiPlayer = WanJiaController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* ZengQiang = BenDiPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (IMC_Move)
				{
					ZengQiang->AddMappingContext(IMC_Move, 0);
				}
			}
		}
	}
}

// Called every frame
void AMy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定输入映射
	if(UEnhancedInputComponent* ZengQiangComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(IA_Move)
		{
			ZengQiangComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
			ZengQiangComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &ThisClass::MoveInput_WanCheng);
		}
		if(IA_ShuBiao_YiDong)
		{
			ZengQiangComponent->BindAction(IA_ShuBiao_YiDong, ETriggerEvent::Triggered, this, &ThisClass::ShuBiao_YiDongInput);;
		}
		if(IA_Jump)
		{
			ZengQiangComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ThisClass::JumpInput);
		}
		if(IA_Shift)
		{
			ZengQiangComponent->BindAction(IA_Shift, ETriggerEvent::Started, this, &ThisClass::ShiftInput);
		}
		if(IA_E)
		{
			ZengQiangComponent->BindAction(IA_E, ETriggerEvent::Triggered, this, &ThisClass::ShiQuInput);
		}
		if(IA_GongJi)
		{
			ZengQiangComponent->BindAction(IA_GongJi, ETriggerEvent::Started, this, &ThisClass::GongtjiInput);
		}
		if(IA_Tab)
		{
			ZengQiangComponent->BindAction(IA_Tab, ETriggerEvent::Started, this, &ThisClass::BeiBaoInPut);
		}
		if(IA_Dun)
		{
			ZengQiangComponent->BindAction(IA_Dun, ETriggerEvent::Started, this, &ThisClass::DunXiaInPut);
		}
		if(IA_Q)
		{
			ZengQiangComponent->BindAction(IA_Q, ETriggerEvent::Started, this, &ThisClass::QingKongShouShangWuPin);
		}
	}

}

