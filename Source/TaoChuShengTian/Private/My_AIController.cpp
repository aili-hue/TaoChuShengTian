// Fill out your copyright notice in the Description page of Project Settings.


#include "My_AIController.h"

void AMy_AIController::BeginPlay()
{
	Super::BeginPlay();
	//运行行为树
	if(RunBehaviorTree(BehaviorTree))
	{

	}
}
