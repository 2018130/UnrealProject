// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	AMyAIController();

	float AISightRadius = 500.f;
	float AISightAge = 5.f;
	float AILoseSightRadius = AISightRadius + 50;
	float AIFieldOfView = 45.f;

	class UAISenseConfig_Sight* SenseConfig_Sight;
	
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawn);
};
