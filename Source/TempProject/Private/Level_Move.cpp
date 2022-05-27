// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Move.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevel_Move::ALevel_Move()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}


 void ALevel_Move::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UGameplayStatics::OpenLevel(GetWorld(), TransferLevelName);
}
