// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/Item_BulletActor.h"


#include "Components/SphereComponent.h"

AItem_BulletActor::AItem_BulletActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}