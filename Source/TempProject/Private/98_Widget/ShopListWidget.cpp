// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/ShopListWidget.h"

#include "98_Widget/ButtonWidget.h"
#include "Components/TextBlock.h"

void UShopListWidget::SetCategoryText(FText NewCategoryTextBlock)
{
	TextBlock_Category->SetText(NewCategoryTextBlock);
	UMG_BuyButton->Category = Category;
}

void UShopListWidget::SetCostText(FText NewCostTextBlock)
{
	TextBlock_Cost->SetText(NewCostTextBlock);
	CostValue = FCString::Atoi(*TextBlock_Cost->GetText().ToString());
	UMG_BuyButton->Cost = CostValue;
}
