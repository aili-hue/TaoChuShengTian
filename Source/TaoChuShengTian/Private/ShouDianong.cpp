// Fill out your copyright notice in the Description page of Project Settings.


#include "ShouDianong.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SpotLightComponent.h"

#include "JueSe/My_Character.h"

AShouDianong::AShouDianong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(StaticMeshComponent);
	SpotLightComponent->SetIntensity(0.f);
}

void AShouDianong::BindWeiTuo()
{
	Character = Cast<AMy_Character>(GetOwner());

	if (Character.IsValid())
	{
		Character->DaiKai.BindUObject(this, &ThisClass::ShouDianTongKaiGuan);

		Character->bShiFouYongYou = true;
	}
}

//设置灯光亮度
void AShouDianong::ShouDianTongKaiGuan(bool bShiFouKaiQi)
{
	if(bShiFouKaiQi)
	{
		SpotLightComponent->SetIntensity(14000);
	}
	else
	{
		SpotLightComponent->SetIntensity(0.f);

	}
}

// Called when the game starts or when spawned
void AShouDianong::BeginPlay()
{
	Super::BeginPlay();

	BindWeiTuo();

}

void AShouDianong::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Character->bShiFouYongYou = false;
	if(Character->DaiKai.IsBound())
	{
		Character->DaiKai.Unbind();
	}
	Character = nullptr;
	Super::EndPlay(EndPlayReason);
}

