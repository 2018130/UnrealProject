// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Task/BTTask_RandomMove.h"

#include "AIController.h"
#include "MyAIController.h"
#include "01_AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(BlackboardComp != nullptr)
	{
		auto Rot = BlackboardComp->GetValueAsRotator("AIRotation");
		auto Controller = OwnerComp.GetOwner<AMyAIController>();
		if(Controller != nullptr)
		{
			auto Owner = Cast<AAICharacter>(Controller->GetPawn());
			if(Controller != nullptr)
			{
				//Controller->SetControlRotation(Rot);
				FVector DirectionVector = FRotationMatrix(Rot).GetUnitAxis(EAxis::X); 
				FVector DestVector = DirectionVector * Distance + Owner->GetActorLocation();
				Controller->MoveToLocation(DestVector);

				return EBTNodeResult::Succeeded;
			}

		}
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
