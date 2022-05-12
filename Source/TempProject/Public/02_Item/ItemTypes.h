// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> ItemActorObject;

	UPROPERTY(EditAnywhere)
		FName ItemCode;

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

UCLASS()
class TEMPPROJECT_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
};
