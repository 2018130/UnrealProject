// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Collision/CollidableActor.h"

#include "Components/SphereComponent.h"
#include "MovablePlayerCharacter.h"

#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollidableActor::ACollidableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);

	OverlapParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("OverlapParticleComponent");
	OverlapParticleComponent->SetupAttachment(RootComponent);
}

void ACollidableActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OverlapParticleComponent->DeactivateSystem();
}

// Called when the game starts or when spawned
void ACollidableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollidableActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->IsA<AMovablePlayerCharacter>())
	{
		OverlapParticleComponent->ActivateSystem();
	}
}

void ACollidableActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	UGameplayStatics::SpawnEmitterAtLocation(this, EndOverlapParticle, this->GetActorLocation());

	OverlapParticleComponent->DeactivateSystem();
}
