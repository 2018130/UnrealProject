// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/00_Weapon/Weapon_ItemActor.h"
#include "Weapon_GrenadeActor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AWeapon_GrenadeActor : public AItemActor
{
	GENERATED_BODY()

protected:
	AWeapon_GrenadeActor();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
		USoundWave* ExplosionSound;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	
	FTimerHandle TimerHandle;
	
	class AMovablePlayerCharacter* player;

	void Explosion();

public:

	void SetOnwer(AMovablePlayerCharacter* InitPlayer) { player = InitPlayer; }

	UStaticMeshComponent* GetMeshComponent() { return StaticMeshComponent; }

	virtual void InitGenericItemInformation() override;
};
