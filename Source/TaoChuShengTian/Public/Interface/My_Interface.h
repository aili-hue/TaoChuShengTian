
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "My_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMy_Interface : public UInterface
{
	GENERATED_BODY()
};

class TAOCHUSHENGTIAN_API IMy_Interface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void ZhiXing();
	UFUNCTION(BlueprintNativeEvent)
	void GuangBiPengZhuangVeiTuo();

};
