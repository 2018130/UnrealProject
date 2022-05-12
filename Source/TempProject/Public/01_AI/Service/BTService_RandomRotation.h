// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RandomRotation.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTService_RandomRotation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	int32 Count = 0;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
