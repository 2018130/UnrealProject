// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	class AMovablePlayerCharacter* Player;

	UPROPERTY(BlueprintReadWrite)
		int32 GI_AICount;

	UPROPERTY(BlueprintReadWrite)
		int32 GI_Score;
	UPROPERTY(BlueprintReadWrite)
		int32 GI_BulletCount;
	UPROPERTY(BlueprintReadWrite)
		int32 GI_Money;
	UPROPERTY(BlueprintReadWrite)
		float GI_ShootDelay;

	UPROPERTY(BlueprintReadWrite)
		float GI_HP;
	UPROPERTY(BlueprintReadWrite)
		float GI_MaxHP;
	UPROPERTY(BlueprintReadWrite)
		float GI_MP;
	UPROPERTY(BlueprintReadWrite)
		float GI_MaxMP;
	UPROPERTY(BlueprintReadWrite)
		float GI_Damage;
public:
	virtual void Init() override;

	virtual FGameInstancePIEResult InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params) override;

	void InitLocalToGIVariable();

	void SetPlayer(class AMovablePlayerCharacter* NewPlayer) { Player = NewPlayer; }

	int32 GetGI_AICount() { return GI_AICount; }
	void SetGI_AICount(int32 Value) { GI_AICount = Value; }

	int32 GetGI_Score() { return GI_Score; }
	int32 GetGI_BulletCount() { return GI_BulletCount; }
	int32 GetGI_Money() { return GI_Money; }
	float GetGI_ShootDelay() { return GI_ShootDelay; }

	float GetGI_HP() { return GI_HP; }
	float GetGI_MaxHP() { return GI_MaxHP; }
	float GetGI_MP() { return GI_MP; }
	float GetGI_MaxMP() { return GI_MaxMP; }
	float GetGI_Damage() { return GI_Damage; }

	AMovablePlayerCharacter* GetPlayer() { return Player; }
};
