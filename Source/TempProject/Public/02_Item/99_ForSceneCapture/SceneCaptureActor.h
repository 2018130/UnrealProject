// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneCaptureActor.generated.h"

UCLASS()
class TEMPPROJECT_API ASceneCaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneCaptureActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class USceneCaptureComponent2D* SceneCaptureComponent;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
