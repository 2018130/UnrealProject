// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "MovableCharacter.h"
#include "MovablePlayerCharacter.h"
#include "01_AI/AICharacter.h"
#include "02_Item/00_Weapon/Weapon_ItemActor.h"
#include "03_GameInstance/MyGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "98_Widget/AIProgressBarWidget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AMyAIController::AMyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent")));

	SenseConfig_Sight->SightRadius = AISightRadius;
	SenseConfig_Sight->LoseSightRadius = AILoseSightRadius;
	SenseConfig_Sight->SetMaxAge(AISightAge);
	SenseConfig_Sight->PeripheralVisionAngleDegrees = AIFieldOfView;

	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	GetPerceptionComponent()->ConfigureSense(*SenseConfig_Sight);
	//GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetected);
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn != nullptr) {
		Cast<AAICharacter>(InPawn)->GetMesh()->SetCollisionProfileName("EnemyPreset");
	}
	auto AI = Cast<AAICharacter>(InPawn);
	if (AI != nullptr)
	{
		RunBehaviorTree(AI->GetBehaviorTree());

		AWeapon_ItemActor* Weapon = Cast<AWeapon_ItemActor>(AI->GetWeaponActorComponent()->GetChildActor());
		if (Weapon != nullptr)
		{
			Weapon->GetMesh()->SetAnimationMode(EAnimationMode::AnimationCustomMode);
			Weapon->GetMesh()->SetAnimInstanceClass(AI->GetWeaponAnimBPAsset()->GetAnimBlueprintGeneratedClass());
		}

		auto GI = GetGameInstance<UMyGameInstance>();
		if(GI != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject("Target", GI->GetPlayer());
		}
	}
}
/*
void AMyAIController::OnPawnDetected(AActor* Target, FAIStimulus Stimulus)
{
	if (Target != nullptr) {
		const auto BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp != nullptr)
		{
			auto Value = BlackboardComp->GetValueAsObject("Target");
			if (Value == nullptr)
			{

				BlackboardComp->SetValueAsObject("Target", Target);
			}
		}
	}
}
*/