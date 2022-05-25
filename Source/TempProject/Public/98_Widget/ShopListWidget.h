// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopListWidget.generated.h"

/**
 * 
 */
enum class EListCategory
{
	NONE,
	DAMAGE,
	BULLETCOUNT,
	MaxHP,
	AttSpd,
};
UCLASS()
class TEMPPROJECT_API UShopListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	EListCategory Category;

	UPROPERTY(VisibleAnywhere)
		class UTextBlock* TextBlock_Category;

	UPROPERTY(VisibleAnywhere)
		class UTextBlock* TextBlock_Cost;

	UPROPERTY(VisibleAnywhere)
		class UButtonWidget* UMG_BuyButton;

	int32 CostValue;

public:
	int32 GetCostValue() { return CostValue; }

	EListCategory GetListCategory() { return Category; }

	void SetCategory(EListCategory NewCategory) { Category = NewCategory; }

	void SetCategoryText(FText NewCategoryTextBlock);

	void SetCostText(FText NewCostTextBlock);
};
