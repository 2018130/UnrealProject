// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "MovablePlayerCharacter.h"
#include "98_Widget/MainWidget.h"
#include "98_Widget/TimerUserWidget.h"
#include "98_Widget/ZoomTargetPointWidget.h"

void ATestPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (TimerWidgetObject != nullptr)
	{
		TimerWidget = Cast<UTimerUserWidget>(CreateWidget(this, TimerWidgetObject));
		TimerWidget->AddToViewport();

		if (MainWidgetObject != nullptr)
		{
			if (ZoomTargetPointWidgetObject != nullptr)
			{
				ZoomTargetPointWidget = Cast<UZoomTargetPointWidget>(CreateWidget(this, ZoomTargetPointWidgetObject));
				ZoomTargetPointWidget->SetVisibility(ESlateVisibility::Hidden);
				ZoomTargetPointWidget->AddToViewport();
			}

			MainWidget = Cast<UMainWidget>(CreateWidget(this, MainWidgetObject));
			MainWidget->AddToViewport();

			auto player = Cast<AMovablePlayerCharacter>(InPawn);
			if (player != nullptr)
			{
				player->OnChangedHP.AddUniqueDynamic(MainWidget, &UMainWidget::OnChangedHPPercentEvent);
				player->OnChangedMP.AddUniqueDynamic(MainWidget, &UMainWidget::OnChangedMPPercentEvent);
				player->OnChangedHP.Broadcast(player);
				player->OnChangedMP.Broadcast(player);
				player->RifleMode();
				player->AddMoney(0);
				player->AddBullet(0);
			}
		}
	}
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

