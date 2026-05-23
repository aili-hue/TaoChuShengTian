// Fill out your copyright notice in the Description page of Project Settings.


#include "WuQiActor/My_WuQi_Actor.h"
#include"Components/StaticMeshComponent.h"
#include"Components/CapsuleComponent.h"

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

// Called when the game starts or when spawned
void AMy_WuQi_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMy_WuQi_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

