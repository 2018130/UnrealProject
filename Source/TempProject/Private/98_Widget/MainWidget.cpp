// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/MainWidget.h"

#include "98_Widget/AskPickUpItemWidget.h"
#include "MovableCharacter.h"
#include "ShopWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UMG_AskPickUpItem->SetVisibility(ESlateVisibility::Hidden);
	UMG_Shop->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OnChangedHPPercentEvent(AMovableCharacter* Character)
{
	if(ProgressBar_HP != nullptr)
	{
		ProgressBar_HP->SetPercent(Character->GetHP() / Character->GetMaxHP());
	}
}

void UMainWidget::OnChangedMPPercentEvent(AMovableCharacter* Character)
{
	if (ProgressBar_MP != nullptr)
	{
		ProgressBar_MP->SetPercent(Character->GetMP() / Character->GetMaxMP());
	}
}

void UMainWidget::SetScore(FText NewScore)
{
	TextBlock_Score->SetText(NewScore);
}
