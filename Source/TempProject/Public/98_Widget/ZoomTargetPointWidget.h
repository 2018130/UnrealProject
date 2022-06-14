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
	UPROPERTY(VisibleAnywhere)
		class UCanvasPanel* CanvasPanel_Panel;
	UPROPERTY(VisibleAnywhere)
		class UImage* Image_Up;
	UPROPERTY(VisibleAnywhere)
		class UImage* Image_Down;
	UPROPERTY(VisibleAnywhere)
		class UImage* Image_Left;
	UPROPERTY(VisibleAnywhere)
		class UImage* Image_Right;

public:
	void Spread();
};
