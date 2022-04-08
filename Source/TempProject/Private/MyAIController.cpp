// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

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
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->ConfigureSense(*SenseConfig_Sight);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetected);
}

void AMyAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawn)
{
	if(DetectedPawn.Num() != 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Pawn detected"));
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("Pawn dont detected"));
	}
}
