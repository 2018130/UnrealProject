
// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/TimerUserWidget.h"

#include "Components/TextBlock.h"

void UTimerUserWidget::SetTimeText(int32 NewTime)
{
	FText Str = FText::FromString(FString::FormatAsNumber(NewTime / 60) + " : " + FString::FormatAsNumber(NewTime % 60));
	TextBlock_Time->SetText(Str);
}

void UTimerUserWidget::SetTimeText(FText NewText)
{
	TextBlock_Time->SetText(NewText);
}