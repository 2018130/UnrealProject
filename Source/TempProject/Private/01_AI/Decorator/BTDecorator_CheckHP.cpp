// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Decorator/BTDecorator_CheckHP.h"

#include "AIController.h"
#include "MyAIController.h"
#include "01_AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UBTDecorator_CheckHP::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto AIController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if(AIController != nullptr)
	{
		auto AI = AIController->GetPawn<AAICharacter>();
		if (AI->GetHP() != AI->GetMaxHP())
		{
			return true;
		}
	}

	return false;
}
