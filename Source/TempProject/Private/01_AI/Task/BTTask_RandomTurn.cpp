// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Task/BTTask_RandomTurn.h"

#include "AIController.h"
#include "01_AI/AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UBTTask_RandomTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackBoardComponent != nullptr && time == 3)
	{
		FRotator Rot(0, FMath::RandRange(0, 360), 0);

		BlackBoardComponent->SetValueAsRotator("AIRotation", Rot);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_RandomTurn::CountDown, 1.0f, true);
		return EBTNodeResult::Succeeded;
	}


	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_RandomTurn::CountDown()
{
	if(time == 0)
	{
		time = 3;
	}else
	{
		time--;
	}
}
