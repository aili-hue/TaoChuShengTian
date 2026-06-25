// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Character.h"
#include"Components/BoxComponent.h"
#include "JueSe/My_Character.h"

// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetMesh(), TEXT("lowerarm_l"));
	BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
}


void AAI_Character::GongJiJvLiPanDuan(AMy_Character* WanJia)
{
	if (bGongJiZhong || !WanJia)return;
	float JvLi = FVector::DistSquaredXY(GetActorLocation(), WanJia->GetActorLocation());

	if (JvLi <= GongJiJvLi)bGongJiZhong = true;
	BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
	GongJiZhiXing();
}
void AAI_Character::GongJiZhiXing()
{
	if (!bGongJiZhong)return;

	GongJi();
	UE_LOG(LogTemp, Log, TEXT("攻击"));
}

void AAI_Character::GuangBiPengZhuangShiJian()
{
	bGongJiZhong = false;
	GongJiYiCi = false;
	BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
	UE_LOG(LogTemp, Log, TEXT("关闭"));

}

void AAI_Character::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bGongJiZhong|| GongJiYiCi)return;
	if (OtherActor && OtherActor != this)
	{
		GongJiYiCi = true;
		UE_LOG(LogTemp, Log, TEXT("测试"));
	}

}

void AAI_Character::YunXing_Implementation(AActor* WanJia)
{
	if (AMy_Character* Character = Cast<AMy_Character>(WanJia))
	{
		GongJiJvLiPanDuan(Character);
	}
}


// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();

	//攻击距离平方
	GongJiJvLi = GongJiJvLi * GongJiJvLi;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);

}
// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

