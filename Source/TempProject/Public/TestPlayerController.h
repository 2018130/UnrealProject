// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UTimerUserWidget> TimerWidgetObject;
	
	UTimerUserWidget* TimerWidget;

	virtual void OnPossess(APawn* InPawn) override;

public:
	UTimerUserWidget* GetTimerWidget() { return TimerWidget; }
};
