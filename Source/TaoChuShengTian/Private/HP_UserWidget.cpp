// Fill out your copyright notice in the Description page of Project Settings.


#include "HP_UserWidget.h"

FLinearColor UHP_UserWidget::HP_Zhuang_Cool(float HP)
{
	if (HP <= 100 && HP >= 50)
	{
		return{ 1.0f, 1.0f, 1.0f, 1.0f };
	}
	else if (HP <= 50 && HP >= 30)
	{
		return { 1.0f, 1.0f, 0.0f, 1.0f };
	}
	return { 1.0f, 0.0f, 0.0f, 1.0f };
}
