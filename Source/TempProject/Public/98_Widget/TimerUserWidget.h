// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UTimerUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UTextBlock* TextBlock_Time;

public:
	void SetTimeText(int32 NewTime);
	void SetTimeText(FText NewTime);
};
