// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PlayAttackMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTTask_PlayAttackMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	UBTTask_PlayAttackMontage();

	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage_Attack;
	UPROPERTY()
		class AMyAIController* AIController;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void EndTask();
};
