// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_WuPin.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include "JueSe/My_Character.h"
#include "My_GameModeBase.h"
#include"Kismet/GameplayStatics.h"
// Sets default values
AActor_WuPin::AActor_WuPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//设置物理模拟
	StaticMeshComponent->SetSimulatePhysics(true);

	StaticMeshGaoGuang=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshGaoGuang"));
	StaticMeshGaoGuang->SetupAttachment(StaticMeshComponent);

	StaticMeshGaoGuang->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 高光不需要碰撞
	StaticMeshGaoGuang->SetVisibility(false);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(StaticMeshComponent);

}


void AActor_WuPin::FuYuMyShuJv(UMyPrimaryDataAsset* ChuDiShuJv)
{
	if(ChuDiShuJv)
	{
		WuPinShuJu = ChuDiShuJv;
	}
}

void AActor_WuPin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor && OtherActor != this)
	{
		//获取角色指针并绑定委托
		ZhiZhenMyCharacter = Cast<AMy_Character>(OtherActor);
		if (!ZhiZhenMyCharacter.IsValid())return;

		//显示高光并设置触发标志
		bIsChongDie = true;
		StaticMeshGaoGuang->SetVisibility(bIsChongDie);

		//如果委托未绑定，则绑定委托
		if (!WeiTuoJvBing.IsValid())
		{
			WeiTuoJvBing = ZhiZhenMyCharacter->ShiQuWeiTuo.AddUObject(this, &ThisClass::ChuFaShiQuWeiTuo);
		}
	}

}

void AActor_WuPin::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bIsChongDie = false;
		StaticMeshGaoGuang->SetVisibility(bIsChongDie);
		//如果委托已绑定，则解绑委托
		if (WeiTuoJvBing.IsValid()&& ZhiZhenMyCharacter.IsValid())
		{
			//解绑委托
			ZhiZhenMyCharacter->ShiQuWeiTuo.Remove(WeiTuoJvBing);
			//重置委托句柄
			WeiTuoJvBing.Reset();
		}

		//重置角色弱指针
		ZhiZhenMyCharacter = nullptr;

	}
}
void AActor_WuPin::ChuFaShiQuWeiTuo()
{
	if(bIsChongDie)
	{
		if (ZhiZhenMyCharacter.IsValid())
		{
			if(ZhiZhenMyCharacter->ChuLiShiQu(this, WuPinShuJu))
			{
				//如果角色成功拾取物品，就销毁物品
				Destroy();
			}
			WeiTuoJvBing.Reset();
		}
		bIsChongDie = false;
	}
}
// Called when the game starts or when spawned
void AActor_WuPin::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

	//根据物品数据资产设置静态网格体和高光材质

	if(WuPin_ShuJv.Contains(WuPinShuJu)&& WuPinShuJu)
	{
		//字典中包含物品数据资产

		StaticMeshComponent->SetStaticMesh(WuPin_ShuJv[WuPinShuJu]);
		StaticMeshGaoGuang->SetStaticMesh(WuPin_ShuJv[WuPinShuJu]);
		StaticMeshGaoGuang->SetMaterial(0,GaoGuangCaiZhi);

		StaticMeshGaoGuang->SetVisibility(bIsChongDie);

	}

}

void AActor_WuPin::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AMy_GameModeBase* MyGameMode_WuPin = Cast<AMy_GameModeBase>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode_WuPin)
	{
		MyGameMode_WuPin->MyXingWuPin(this);
	}
}

void AActor_WuPin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(ZhiZhenMyCharacter.IsValid())
	{
		ZhiZhenMyCharacter->ShiQuWeiTuo.RemoveAll(this);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AActor_WuPin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

