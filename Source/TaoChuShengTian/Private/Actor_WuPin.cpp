// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_WuPin.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SphereComponent.h"
#include "JueSe/My_Character.h"
#include"Kismet/GameplayStatics.h"
// Sets default values
AActor_WuPin::AActor_WuPin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	StaticMeshGaoGuang=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshGaoGuang"));
	StaticMeshGaoGuang->SetupAttachment(StaticMeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(StaticMeshComponent);
}


void AActor_WuPin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor && OtherActor != this)
	{
		//获取角色指针并绑定委托
		MyCharacter = Cast<AMy_Character>(OtherActor);
		if (!MyCharacter.IsValid())return;

		//显示高光并设置触发标志
		bIsChongDie = true;
		StaticMeshGaoGuang->SetVisibility(true);

		//如果委托未绑定，则绑定委托
		if (!WeiTuoJvBing.IsValid())
		{
			WeiTuoJvBing = MyCharacter->ShiQuWeiTuo.AddUObject(this, &ThisClass::ChuFaShiQuWeiTuo);
		}
	}

}

void AActor_WuPin::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bIsChongDie = false;
		StaticMeshGaoGuang->SetVisibility(false);
		//如果委托已绑定，则解绑委托
		if (WeiTuoJvBing.IsValid())
		{
			//解绑委托
			MyCharacter->ShiQuWeiTuo.Remove(WeiTuoJvBing);
			//重置委托句柄
			WeiTuoJvBing.Reset();
		}

		//重置角色弱指针
		MyCharacter = nullptr;

	}
}
void AActor_WuPin::ChuFaShiQuWeiTuo()
{
	if(bIsChongDie)
	{
		if (MyCharacter.IsValid())
		{
			MyCharacter->ChuLiShiQu(this, WuPinShuJu);
			WeiTuoJvBing.Reset();
		}
		bIsChongDie = false;
	}
	Destroy();

}
// Called when the game starts or when spawned
void AActor_WuPin::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

}

void AActor_WuPin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(MyCharacter.IsValid())
	{
		MyCharacter->ShiQuWeiTuo.RemoveAll(this);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AActor_WuPin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

