// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Decorator/BTDecorator_IsTargetExist.h"

#include "MyAIController.h"
#include "01_AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_IsTargetExist::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto Controller = OwnerComp.GetOwner<AAIController>();
	if (Controller != nullptr && !Controller->GetPawn<AAICharacter>()->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		if (Controller->GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
		{
			return true;
		}
	}
	return false;
}
