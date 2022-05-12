// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowGetMoneyWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UShowGetMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
		class UTextBlock* TextBlock_Money;

public:
	void SetMoneyTextBlock(int32 Value);
};
