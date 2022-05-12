// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/99_ForSceneCapture/SceneCaptureActor.h"

#include "Components/SceneCaptureComponent2D.h"

// Sets default values
ASceneCaptureActor::ASceneCaptureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASceneCaptureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneCaptureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

