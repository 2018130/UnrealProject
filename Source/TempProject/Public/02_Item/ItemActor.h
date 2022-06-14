// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class TEMPPROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
		FName ItemCode;
	UPROPERTY(EditAnywhere)
		UDataTable* DataTable;
	UPROPERTY(VisibleAnywhere)
		FGenericItemInformation GenericItemInformation;
public:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void InitGenericItemInformation();

};
