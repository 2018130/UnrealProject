// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Move.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevel_Move::ALevel_Move()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));

	RootComponent = TransferVolume;

	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevel_Move::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevel_Move::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


 void ALevel_Move::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UGameplayStatics::OpenLevel(GetWorld(), TransferLevelName);
}
