// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/ItemActor.h"
#include "Weapon_ItemActor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AWeapon_ItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	AWeapon_ItemActor();

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMeshComponent;

public:
	USkeletalMeshComponent* GetMesh() { return SkeletalMeshComponent; }
};
