// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollidableActor.generated.h"

UCLASS()
class TEMPPROJECT_API ACollidableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollidableActor();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* OverlapParticleComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* EndOverlapParticle;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

};
