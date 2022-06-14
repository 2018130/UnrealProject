// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Collision/SpawnerActor.h"

#include "01_AI/AICharacter.h"
#include "03_GameInstance/MyGameInstance.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerActor::Spawn, SpawnInterval, true);
}

void ASpawnerActor::Spawn()
{
	auto GI = Cast<UMyGameInstance>(GetGameInstance());

	if (SpawnType != nullptr &&  GI != nullptr) {
		if (GI->GetGI_AICount() >= 20)return;

		GetWorld()->SpawnActor<AAICharacter>(SpawnType, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
		GI->SetGI_AICount(GI->GetGI_AICount() + 1);
	}
}

