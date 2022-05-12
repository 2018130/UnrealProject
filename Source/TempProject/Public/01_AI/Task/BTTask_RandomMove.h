// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTTask_RandomMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		float Distance;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
