// Fill out your copyright notice in the Description page of Project Settings.


#include "03_GameInstance/MyGameInstance.h"

#include "MovablePlayerCharacter.h"
#include "TestPlayerController.h"
#include "98_Widget/MainWidget.h"
#include "Kismet/GameplayStatics.h"

FGameInstancePIEResult UMyGameInstance::InitializeForPlayInEditor(int32 PIEInstanceIndex,
	const FGameInstancePIEParameters& Params)
{
	GI_Score = 0;
	GI_BulletCount = 0;
	GI_Money = 0;
	GI_ShootDelay = 0.4;
	GI_HP = 100;
	GI_MaxHP = 100;
	GI_MP = 100;
	GI_MaxMP = 100;
	GI_Damage = 20;

	return Super::InitializeForPlayInEditor(PIEInstanceIndex, Params);
}

void UMyGameInstance::InitLocalToGIVariable()
{
	if (Player != nullptr) {
		auto Controller = Player->GetController<ATestPlayerController>();
		if (Controller != nullptr) {
			GI_Score = Controller->GetMainWidget()->GetScore();
			GI_BulletCount = Player->GetBulletCount();
			GI_Money = Player->GetMoney();
			GI_ShootDelay = Player->GetShootDelay();
			GI_HP = Player->GetHP();
			GI_MaxHP = Player->GetMaxHP();
			GI_MP = Player->GetMP();
			GI_MaxMP = Player->GetMaxMP();
			GI_Damage = Player->GetDamage();
		}
	}
}
