// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"

#include "98_Widget/ShopListWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(UMG_BulletList != nullptr)
	{
		UMG_BulletList->SetCategory(EListCategory::BULLETCOUNT);
		UMG_BulletList->SetCategoryText(FText::FromString("Bullet 10 Cost : "));
		UMG_BulletList->SetCostText(FText::FromString("5"));
	}

	if (UMG_DamageList != nullptr)
	{
		UMG_DamageList->SetCategory(EListCategory::DAMAGE);
		UMG_DamageList->SetCategoryText(FText::FromString("Damage 1 Cost : "));
		UMG_DamageList->SetCostText(FText::FromString("10"));
	}

	if (UMG_HPList != nullptr)
	{
		UMG_HPList->SetCategory(EListCategory::MaxHP);
		UMG_HPList->SetCategoryText(FText::FromString("MaxHP 10 Cost : "));
		UMG_HPList->SetCostText(FText::FromString("5"));
	}

	if (UMG_AttSpdList != nullptr)
	{
		UMG_AttSpdList->SetCategory(EListCategory::AttSpd);
		UMG_AttSpdList->SetCategoryText(FText::FromString("AttSpd 0.01 Cost : "));
		UMG_AttSpdList->SetCostText(FText::FromString("10"));
	}
}
