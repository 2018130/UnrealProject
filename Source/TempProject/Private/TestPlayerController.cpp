// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "MovablePlayerCharacter.h"
#include "03_GameInstance/MyGameInstance.h"
#include "98_Widget/MainWidget.h"
#include "98_Widget/TimerUserWidget.h"
#include "98_Widget/ZoomTargetPointWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

				auto GI = Cast<UMyGameInstance>(GetGameInstance());
				if(GI != nullptr)
				{
					GI->SetPlayer(player);
					player->InitGIVariableToLocal();
				}
			}
		}
	}
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPlayerController::AsyncLevelLoad(const FString& LevelDir, const FString& LevelName)
{
	LoadPackageAsync(LevelDir + LevelName, FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadPackage, EAsyncLoadingResult::Type Result)
		{
			if (Result == EAsyncLoadingResult::Succeeded)
			{
				AsyncLevelLoadFinished(LevelName);
			}
		}),0,PKG_ContainsMap);
}

void ATestPlayerController::AsyncLevelLoadFinished(const FString& LevelName)
{
	UGameplayStatics::OpenLevel(this, "ElvenRuins");
}

