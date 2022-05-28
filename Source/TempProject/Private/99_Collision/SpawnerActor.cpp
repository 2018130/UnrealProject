// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Collision/SpawnerActor.h"

#include "01_AI/AICharacter.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerActor::Spawn, SpawnInterval, true);
}

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerActor::Spawn()
{
	if (SpawnType != nullptr) {
		GetWorld()->SpawnActor<AAICharacter>(SpawnType, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
	}
}

