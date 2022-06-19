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
		TSubclassOf<class UMainWidget> MainWidgetObject;

	UMainWidget* MainWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UTimerUserWidget> TimerWidgetObject;
	
	UTimerUserWidget* TimerWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UZoomTargetPointWidget> ZoomTargetPointWidgetObject;

	UZoomTargetPointWidget* ZoomTargetPointWidget;

	virtual void OnPossess(APawn* InPawn) override;
	
public:
	virtual void BeginPlay() override;

	UMainWidget* GetMainWidget() { return MainWidget; }

	UZoomTargetPointWidget* GetZoomTargetPointWidget() { return ZoomTargetPointWidget; }

	UTimerUserWidget* GetTimerWidget() { return TimerWidget; }

	UFUNCTION(BlueprintCallable)
		void AsyncLevelLoad(const FString& LevelDir, const FString& LevelName);


private:

	void AsyncLevelLoadFinished(const FString& LevelName);
};
