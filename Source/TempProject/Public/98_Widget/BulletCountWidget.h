// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletCountWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UBulletCountWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		class UTextBlock* TextBlock_BulletCount;

public:
	void SetTextBlock_BulletCount(int32 Value);
};
