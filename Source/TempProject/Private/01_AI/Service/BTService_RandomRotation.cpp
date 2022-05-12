// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Service/BTService_RandomRotation.h"

#include "BehaviorTree/BlackboardComponent.h"

void UBTService_RandomRotation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if(Count % 6 == 0)
	{
		auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
		if(BlackBoardComponent != nullptr)
		{
			FRotator Rot(0, FMath::RandRange(0, 360), 0);
			BlackBoardComponent->SetValueAsRotator("AIRotation", Rot);
		}

		if (Count > 1000) Count = 0;
	}

	Count++;
}
