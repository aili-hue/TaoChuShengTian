// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Character.h"
#include"Components/BoxComponent.h"
#include "JueSe/My_Character.h"
#include"Kismet/GameplayStatics.h"
#include "HP/HP_Component.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "My_AIController.h"
#include"BrainComponent.h"
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetMesh(), TEXT("lowerarm_l"));
	BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
	HP_Component = CreateDefaultSubobject<UHP_Component>(TEXT("HP"));
	
}


void AAI_Character::GongJiJvLiPanDuan(AMy_Character* WanJia)
{
	if (bGongJiZhong || !WanJia)return;
	float JvLi = FVector::DistSquaredXY(GetActorLocation(), WanJia->GetActorLocation());

	if (JvLi <= GongJiJvLi)
	{ 
		bGongJiZhong = true; 
		BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
		GongJiZhiXing();
	}
	else
	{
		GuangBiPengZhuangShiJian();
	}
}
void AAI_Character::GongJiZhiXing()
{
	if (!bGongJiZhong)return;

	GongJi();
}

void AAI_Character::GuangBiPengZhuangShiJian()
{
	bGongJiZhong = false;
	GongJiYiCi = false;
	BoxComponent->SetGenerateOverlapEvents(bGongJiZhong);
}

void AAI_Character::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bGongJiZhong|| GongJiYiCi)return;
	if (OtherActor && OtherActor->IsA<AMy_Character>())
	{
		UGameplayStatics::ApplyDamage(OtherActor, ShangHai, GetController(), this, UDamageType::StaticClass());
		GongJiYiCi = true;
	}

}

void AAI_Character::YunXing_Implementation(AActor* WanJia)
{
	if (AMy_Character* Character = Cast<AMy_Character>(WanJia))
	{
		GongJiJvLiPanDuan(Character);
	}
}


void AAI_Character::TingZhiYiDong()
{
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	if(MovementComponent)
	{
		GetCharacterMovement()->StopMovementImmediately();
	}
	AMy_AIController* AIController = Cast<AMy_AIController>(GetController());
	if(AIController)
	{
		if (AIController->GetBrainComponent())
		{
			AIController->GetBrainComponent()->StopLogic("Dead");
		}
	}
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();

	//攻击距离平方
	GongJiJvLi = GongJiJvLi * GongJiJvLi;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);

}
float AAI_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP_Component->DiaoHP(DamageAmount);

	if(HP_Component->GetHP()<=0)
	{
		bSiWang = true;
		TingZhiYiDong();
	}
	else
	{
		if (!bShiFouWanCheng)return 0.f;
		ShouJiDongHua();
	}

	return 0.f;
}
// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

