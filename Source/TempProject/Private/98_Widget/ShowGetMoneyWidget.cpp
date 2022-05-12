// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/ShowGetMoneyWidget.h"

#include "Components/TextBlock.h"

void UShowGetMoneyWidget::SetMoneyTextBlock(int32 Value)
{
	TextBlock_Money->SetText(FText::AsNumber(Value));
}
