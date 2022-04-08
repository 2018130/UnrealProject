// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "MovablePlayerCharacter.h"
#include "98_Widget/TimerUserWidget.h"

void ATestPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(TimerWidgetObject !=nullptr)
	{
		TimerWidget = Cast<UTimerUserWidget>(CreateWidget(this, TimerWidgetObject));
		TimerWidget->AddToViewport();
	}
}
