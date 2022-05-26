// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
		class UProgressBar* ProgressBar_HP;
	UPROPERTY(EditAnywhere)
		class UProgressBar* ProgressBar_MP;
	UPROPERTY(EditAnywhere)
		class UTextBlock* TextBlock_Score;
	UPROPERTY(EditAnywhere)
		class UTextBlock* TextBlock_WeaponType;

	UPROPERTY(EditAnywhere)
		class UAskPickUpItemWidget* UMG_AskPickUpItem;

	UPROPERTY(BlueprintReadOnly)
		class UShowGetMoneyWidget* UMG_Money;

	UPROPERTY(BlueprintReadOnly)
		class UBulletCountWidget* UMG_BulletCount;

	UPROPERTY(BlueprintReadOnly)
		class UShopWidget* UMG_Shop;

	int32 Score;

public:
	
	UFUNCTION()
		void OnChangedHPPercentEvent(class AMovableCharacter* Character);
	UFUNCTION()
		void OnChangedMPPercentEvent(class AMovableCharacter* Character);

	UAskPickUpItemWidget* GetAskPickUpItemWidget() { return UMG_AskPickUpItem; }

	UShowGetMoneyWidget* GetShowGetMoneyWidget() { return UMG_Money; }

	UBulletCountWidget* GetBulletCountWidget() { return UMG_BulletCount; }

	UShopWidget* GetShopWidget() { return UMG_Shop; }

	void AddScore(int32 NewScore);

	int32 GetScore() { return Score; }

	void SetWeaponType(FText NewType) { TextBlock_WeaponType->SetText(NewType); }
};
