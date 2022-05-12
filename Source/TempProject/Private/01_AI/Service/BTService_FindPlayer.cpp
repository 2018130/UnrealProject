// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Service/BTService_FindPlayer.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#include "MyAIController.h"
#include "01_AI/AICharacter.h"


void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = OwnerComp.GetOwner<AMyAIController>();
	if (Controller != nullptr) {
		auto Owner = Controller->GetPawn<AAICharacter>();

		if (Owner != nullptr)
		{
			FHitResult Hits;

			if (UKismetSystemLibrary::SphereTraceSingleForObjects(Owner, Owner->GetActorLocation(), Owner->GetActorLocation() + 1, Radius,
				ObjectType, false, TArray<AActor*>(), EDrawDebugTrace::None, Hits, true))
			{
				//for (int32 i = 0; i < Hits.Num(); i++)
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Hits.GetActor());
				UKismetSystemLibrary::PrintString(this, "target Detected");
				return;
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);
		}
	}
}
