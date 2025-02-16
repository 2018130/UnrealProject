// Fill out your copyright notice in the Description page of Project Settings.


#include "01_AI/Task/BTTask_PlayAttackMontage.h"

#include "GameplayTagsManager.h"
#include "HeadMountedDisplayTypes.h"
#include "MovablePlayerCharacter.h"
#include "MyAIController.h"
#include "01_AI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_PlayAttackMontage::UBTTask_PlayAttackMontage()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_PlayAttackMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = OwnerComp.GetOwner<AMyAIController>();

	if (Controller != nullptr)
	{
		auto AI = Controller->GetPawn<AAICharacter>();
		AI->SetIsAttacking(true);
		//AI->GetMesh()->GetAnimInstance()->Montage_Play(Montage_Attack, 1.0f, EMontagePlayReturnType::Duration);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_PlayAttackMontage::EndTask, 1.0);
		return EBTNodeResult::InProgress;

	}
	return EBTNodeResult::Failed;
}

void UBTTask_PlayAttackMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	AIController = Cast<AMyAIController>(OwnerComp.GetOwner());
	if (AIController != nullptr) {
		auto BlackboardComp = AIController->GetBlackboardComponent();
		if (BlackboardComp != nullptr)
		{
			auto target = BlackboardComp->GetValueAsObject("Target");
			if (target != nullptr)
			{
				auto Target = Cast<AMovablePlayerCharacter>(target);
				if (Target != nullptr && AIController->GetPawn<AAICharacter>()->GetIsAttacking()) {
					Target->TakeDamage(AIController->GetPawn<AAICharacter>()->GetDamage() * 0.1, FDamageEvent(), AIController, nullptr);

					FRotator ToPlayerRot = (Target->GetActorLocation() - AIController->GetPawn<AAICharacter>()->GetActorLocation()).Rotation();
					FRotator ControllRot = AIController->GetControlRotation();
					AIController->GetPawn<AAICharacter>()->SetLookPlayerRotation(ToPlayerRot - ControllRot);
				}
			}
		}
	}
}

void UBTTask_PlayAttackMontage::EndTask()
{
	if (AIController != nullptr) {
		auto AI = AIController->GetPawn<AAICharacter>();
		if (AI != nullptr && !AI->GetDying())
		{
			AI->SetIsAttacking(false);
			//AIController->GetPawn<AAICharacter>()->GetMesh()->GetAnimInstance()->Montage_Stop(0.1);
			//AIController->RunBehaviorTree(AIController->GetPawn<AAICharacter>()->GetBehaviorTree());
			auto BTree = AIController->GetBrainComponent();
			FinishLatentTask(*(Cast<UBehaviorTreeComponent>(BTree)), EBTNodeResult::Succeeded);
		}
	}
}
