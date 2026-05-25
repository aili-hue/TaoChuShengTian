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

//获取角色移动组件

	CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;

//背包组件
	BeiBaoComponent = CreateDefaultSubobject<UMy_BeiBaoComponent>(TEXT("BeiBaoComponent"));

}
//角色移动
void AMy_Character::MoveInput(const FInputActionValue& PlayInput)
{

	FVector2D MoveVector2D = PlayInput.Get<FVector2D>();
	FRotator MoveRotator = Controller->GetControlRotation();
	FRotator MoveControlRotator(0.f, MoveRotator.Yaw, 0.f);
	FVector JvZhen_X = FRotationMatrix(MoveControlRotator).GetUnitAxis(EAxis::Y);
	FVector JvZhen_Y = FRotationMatrix(MoveControlRotator).GetUnitAxis(EAxis::X);
	AddMovementInput(JvZhen_X, MoveVector2D.Y);
	AddMovementInput(JvZhen_Y, MoveVector2D.X);

}

//鼠标移动视角
void AMy_Character::ShuBiao_YiDongInput(const FInputActionValue& PlayInput)
{
	FVector2D ShuBiaoYIDongVector2D = PlayInput.Get<FVector2D>();
	AddControllerYawInput(ShuBiaoYIDongVector2D.X);
	AddControllerPitchInput(ShuBiaoYIDongVector2D.Y);

}

void AMy_Character::JumpInput(const FInputActionValue& PlayInput)
{
	Jump();
}

//角色加速度
void AMy_Character::ShiftInput(const FInputActionValue& PlayInput)
{
	if(CharacterMovementComponent->MaxWalkSpeed == ChuShiYiDongSuDong)
	{
		CharacterMovementComponent->MaxWalkSpeed = MaxYiDongSuDong;
		return;
	}
	CharacterMovementComponent->MaxWalkSpeed = ChuShiYiDongSuDong;
}


void AMy_Character::ShiQuInput(const FInputActionValue& PlayInput)
{
	ShiQuWeiTuo.Broadcast();
}


void AMy_Character::ChuFaPengZhuangFunc(bool bPengZhuang)
{
	ChuFaPengZhuang.ExecuteIfBound(bPengZhuang);
}

void AMy_Character::ChuLiShiQu(AActor* WuPin, UMyPrimaryDataAsset* WuPinShuJu)
{
	//先判断物品和物品数据资产是否有效
	if(!WuPin||!WuPinShuJu)return;
	//将拾取的物品传递给背包组件
	BeiBaoComponent->addWuPin(WuPinShuJu);
	//根据物品数据资产的类型和数量进行相应的处理，比如增加玩家的属性，或者在角色上生成一个新的Actor（比如武器）
	if(WuPinShuJu->CunFangActor)
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
		WeaponActor = GetWorld()->SpawnActor<AActor>(WuPinShuJu->CunFangActor,FVector::ZeroVector,FRotator::ZeroRotator, ShengChengActorCanShu);
	}
	//如果生成了武器Actor，就将它绑定到角色的武器插槽上
	if(WeaponActor)
	{
		//将生成的武器Actor绑定到角色的武器插槽上
		WeaponActor->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, WuQiChaCao);

		//玩家持有近战武器
		if (WuPinShuJu->MYUELeiXing == EMYUELeiXing::WuQi_JinZhan)
		{
			bChiYouJinZhanWuQi = true;
		}

	}
	else
	{
		WeaponActor = nullptr;
		return;
	}
}
void AMy_Character::GuangBiPengZhuang()
{
	//关闭武器碰撞
	bKaiQIPengZhuang = false;
	ChuFaPengZhuangFunc(bKaiQIPengZhuang);
}
void AMy_Character::GongtjiInput(const FInputActionValue& PlayInput)
{
	//如果角色没有武器，就无法攻击
	if (!WeaponActor)return;
	//如果角色持有近战武器，就触发攻击事件
	if (bChiYouJinZhanWuQi&& !bKaiQIPengZhuang)
	{
		//开启武器碰撞
		bKaiQIPengZhuang = true;
		ChuFaPengZhuangFunc(bKaiQIPengZhuang);
		UE_LOG(LogTemp, Warning, TEXT("开启武器碰撞"));
	}
	if(bKaiQIPengZhuang)
	{
		UE_LOG(LogTemp, Warning, TEXT("攻击了！"));
	}

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
	}

}

