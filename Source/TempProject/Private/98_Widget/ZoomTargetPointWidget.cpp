// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/ZoomTargetPointWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"

void UZoomTargetPointWidget::Spread()
{
	if(CanvasPanel_Panel != nullptr && Image_Down != nullptr && Image_Left != nullptr &&
		Image_Right != nullptr && Image_Up != nullptr)
	{
		auto DownSlot = Cast<UCanvasPanelSlot>(Image_Down->Slot.Get());
		FVector2D DownVector = DownSlot->GetAlignment();
		DownVector.Y += 25;
		UKismetSystemLibrary::PrintString(this, DownVector.ToString());
		DownSlot->SetAlignment(DownVector);
	}
}
