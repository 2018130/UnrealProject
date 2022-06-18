// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZoomTargetPointWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UZoomTargetPointWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* Converge;
	UPROPERTY(EditAnywhere)
		class UImage* Image_Up;
	UPROPERTY(EditAnywhere)
		class UImage* Image_Down;
	UPROPERTY(EditAnywhere)
		class UImage* Image_Left;
	UPROPERTY(EditAnywhere)
		class UImage* Image_Right;

public:
	void Spread();
};
