// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/AIProgressBarWidget.h"

#include "Components/ProgressBar.h"
#include "Kismet/KismetSystemLibrary.h"

void UAIProgressBarWidget::SetProgressBar(float Value)
{
	ProgressBar_AI->SetPercent(Value);
}

void UAIProgressBarWidget::DrawColor(FLinearColor Color)
{
	ProgressBar_AI->SetFillColorAndOpacity(Color);
}

void UAIProgressBarWidget::DrawBackColor()
{
	ProgressBar_AI->SetFillColorAndOpacity(FLinearColor::Red);
}
