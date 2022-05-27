// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Level_Move.generated.h"

UCLASS()
class TEMPPROJECT_API ALevel_Move : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel_Move();

private:
	UPROPERTY(EditAnywhere)
		FName TransferLevelName;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComponent;

protected:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

