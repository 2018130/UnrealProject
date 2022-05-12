// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBTService_FindPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
		float Radius;

	UPROPERTY(EditAnywhere)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
