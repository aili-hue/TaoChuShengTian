// Fill out your copyright notice in the Description page of Project Settings.


#include "WuQiActor/My_WuQi_Actor.h"
#include"Components/StaticMeshComponent.h"
#include"Components/CapsuleComponent.h"
#include "JueSe/My_Character.h"
#include"Kismet/GameplayStatics.h"
// Sets default values
AMy_WuQi_Actor::AMy_WuQi_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(StaticMeshComponent);

}

//设置碰撞
void AMy_WuQi_Actor::SetStaticMeshPengZhung(bool KaiGUan)
{
	//切换碰撞状态
	bIsPengZhuang = KaiGUan;
	if (bIsPengZhuang)ShouJiMingDan.Empty();
	CapsuleComponent->SetGenerateOverlapEvents(bIsPengZhuang);
	
}

void AMy_WuQi_Actor::CapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		if (ShouJiMingDan.Contains(OtherActor))return;
		AActor* ChiYouZhe = GetOwner();
		if (!ChiYouZhe)return;
		AController* KongZhiQi = ChiYouZhe->GetInstigatorController();
		if (!KongZhiQi)return;

		ShouJiMingDan.Add(OtherActor);
		UGameplayStatics::ApplyDamage(OtherActor, ShiHai, KongZhiQi, this, UDamageType::StaticClass());
	}
}


void AMy_WuQi_Actor::ZhiXing_Implementation()
{
	if (MyCharacterRuoZhiZhen.IsValid())
	{
		MyCharacterRuoZhiZhen->GongJiIpute();
		MyCharacterRuoZhiZhen->bShiFouJiXuGongJi = false;
	}
	SetStaticMeshPengZhung(true);
}

void AMy_WuQi_Actor::GuangBiPengZhuangVeiTuo_Implementation()
{
	SetStaticMeshPengZhung(false);
	MyCharacterRuoZhiZhen->bShiFouJiXuGongJi = true;
}

// Called when the game starts or when spawned
void AMy_WuQi_Actor::BeginPlay()
{
	Super::BeginPlay();
	//生成时关闭碰撞
	CapsuleComponent->SetGenerateOverlapEvents(bIsPengZhuang);

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::CapsuleBeginOverlap);
	//获取角色指针并绑定委托
	MyCharacterRuoZhiZhen = Cast<AMy_Character>(GetOwner());

}
void AMy_WuQi_Actor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MyCharacterRuoZhiZhen->bShiFouJiXuGongJi = true;
	MyCharacterRuoZhiZhen = nullptr;
	Super::EndPlay(EndPlayReason);
}

