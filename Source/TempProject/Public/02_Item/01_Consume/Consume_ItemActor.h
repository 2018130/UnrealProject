// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/ItemActor.h"
#include "Consume_ItemActor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AConsume_ItemActor : public AItemActor
{
	GENERATED_BODY()

protected:
	AConsume_ItemActor();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;

	virtual void BeginPlay() override;

public:

	float GetRecoverHP();

	float GetRecoverMP();

	virtual void InitGenericItemInformation() override;
};
