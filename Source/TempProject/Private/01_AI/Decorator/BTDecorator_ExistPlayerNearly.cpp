// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Decorator/BTDecorator_ExistPlayerNearly.h"

#include "MovablePlayerCharacter.h"
#include "MyAIController.h"
#include "01_AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_ExistPlayerNearly::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                uint8* NodeMemory) const
{
	auto AIController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		auto AI = AIController->GetPawn<AAICharacter>();
		auto Target = AIController->GetBlackboardComponent()->GetValueAsObject("Target");
		if(Target != nullptr)
		{
			auto Player = Cast<AMovablePlayerCharacter>(Target);
			if(AI->GetDistanceTo(Player) <=  Distance)
			{
				return true;
			}

			return false;
		}
	}
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
