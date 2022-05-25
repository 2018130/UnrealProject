// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere)
		class UShopListWidget* UMG_DamageList;
	UPROPERTY(EditAnywhere)
		class UShopListWidget* UMG_BulletList;
	UPROPERTY(EditAnywhere)
		class UShopListWidget* UMG_HPList;
	UPROPERTY(EditAnywhere)
		class UShopListWidget* UMG_AttSpdList;
};
