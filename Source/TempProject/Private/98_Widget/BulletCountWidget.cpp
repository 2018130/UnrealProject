// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/BulletCountWidget.h"

#include "Components/TextBlock.h"

void UBulletCountWidget::SetTextBlock_BulletCount(int32 Value)
{
	TextBlock_BulletCount->SetText(FText::AsNumber(Value));
}
