// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsTargetExist.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTDecorator_IsTargetExist : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
