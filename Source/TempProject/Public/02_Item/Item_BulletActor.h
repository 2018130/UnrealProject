// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/ItemActor.h"
#include "Item_BulletActor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AItem_BulletActor : public AItemActor
{
	GENERATED_BODY()

protected:
	AItem_BulletActor();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComponent;
};
