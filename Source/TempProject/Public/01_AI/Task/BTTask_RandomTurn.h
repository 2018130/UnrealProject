// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomTurn.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTTask_RandomTurn : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;

	int32 time = 3;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void CountDown();
};
