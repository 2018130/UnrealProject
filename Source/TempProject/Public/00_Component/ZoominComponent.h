// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZoominComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPPROJECT_API UZoominComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZoominComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	void Zoom();

	void ZoomOut();

	bool IsZoomMode() { return IsZoomIn; }
protected:

	UPROPERTY(EditAnywhere)
		float XVal;
	UPROPERTY(EditAnywhere)
		float YVal;
	UPROPERTY(EditAnywhere)
		float ZVal;
	bool IsZoomIn = false;

};
