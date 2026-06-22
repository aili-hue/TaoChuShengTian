
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/My_Interface.h"

#include "Actor_YaoPin.generated.h"


class UStaticMeshComponent;

UCLASS()
class TAOCHUSHENGTIAN_API AActor_YaoPin : public AActor, public IMy_Interface
{
	GENERATED_BODY()
	
public:	

	AActor_YaoPin();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "增加血量数值")
	float ZengJia_HP = 20.f;

	virtual void ZhiXing_Implementation()override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	

};
