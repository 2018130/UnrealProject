// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
 {
	 WEAPON,
	 CONSUME,
 };

USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> ItemActorObject;

	UPROPERTY(EditAnywhere)
		FName ItemCode;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	UPROPERTY(EditAnywhere)
		FString ItemName;

	UPROPERTY(EditAnywhere)
		FString ItemDescription;
};

USTRUCT(BlueprintType)
struct FGenericItemInformation {
	GENERATED_BODY()
public:

	TSharedPtr<FItemInformation> SharedPtr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> ItemActorObject;

	UPROPERTY(EditAnywhere)
		FName ItemCode;

	UPROPERTY(EditAnywhere)
		EItemType ItemType;

	UPROPERTY(EditAnywhere)
		FString ItemName;

	UPROPERTY(EditAnywhere)
		FString ItemDescription;
};

USTRUCT(BlueprintType)
struct FWeapon : public FItemInformation{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float Damage;
};

USTRUCT(BlueprintType)
struct FBullet : public FItemInformation {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FConsume : public FItemInformation {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float RecoverHP;
	UPROPERTY(EditAnywhere)
		float RecoverMP;
};

UCLASS()
class TEMPPROJECT_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
};
