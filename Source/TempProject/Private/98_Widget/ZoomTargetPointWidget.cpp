// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/ZoomTargetPointWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"

void UZoomTargetPointWidget::Spread()
{
	if(Converge != nullptr)
	{
		PlayAnimation(Converge);
	}
}
