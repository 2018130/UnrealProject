// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/ItemTypes.h"
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

	UPROPERTY(VisibleAnywhere)
	    FGenericItemInformation GenericItemInformation;

	UPROPERTY(EditAnywhere)
		USoundWave* ExplosionSound;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;

	UPROPERTY(EditAnywhere)
		FName ItemCode;

	UPROPERTY(EditAnywhere)
		UDataTable* DataTable;

	FTimerHandle TimerHandle;
	
	class AMovablePlayerCharacter* player;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void InitGenericItemInformation();

	void Explosion();

public:

	void SetOnwer(AMovablePlayerCharacter* InitPlayer) { player = InitPlayer; }

	UStaticMeshComponent* GetMeshComponent() { return StaticMeshComponent; }
};
