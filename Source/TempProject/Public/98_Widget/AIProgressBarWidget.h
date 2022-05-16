// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UAIProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	class UProgressBar* ProgressBar_AI;

public:

	void SetProgressBar(float Value);
};
