// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/ButtonWidget.h"

#include "MovablePlayerCharacter.h"
#include "98_Widget/ShopListWidget.h"
#include "Components/Border.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

FReply UButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

FReply UButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Player = GetOwningPlayerPawn<AMovablePlayerCharacter>();
	if ( Player != nullptr)
	{ 
		if (Player->CheckMoney(Cost))
		{
			switch (Category)
			{
			case EListCategory::DAMAGE:
				Player->AddDamage(1);
				break;
			case EListCategory::BULLETCOUNT:
				Player->AddBullet(30);
				break;
			case EListCategory::MaxHP:
				Player->AddMaxHP(10);
				Player->OnChangedHP.Broadcast(Player);
				break;
			case EListCategory::AttSpd:
				float Value = Player->GetShootDelay() - 0.01;
				Player->SetShootDelay(Value);
				if (Value < 0.06) return FReply::Handled();

				break;
			}
			Player->AddMoney(-Cost);
		}
	}

	return FReply::Handled();
}

void UButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Border_Back->SetBrushColor(FLinearColor::Black);
}

void UButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Border_Back->SetBrushColor(FLinearColor::Gray);
}
