// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class TEMPPROJECT_API AAICharacter : public AMovableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
		class ATargetPoint* PointA;
	UPROPERTY(EditAnywhere)
		class ATargetPoint* PointB;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* DeathAsset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Dying;

public:	
	bool GetDying() { return Dying; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ATargetPoint* GetTargetPointA() { return PointA; }
	ATargetPoint* GetTargetPointB() { return PointB; }

	class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

	virtual void Attack() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UWidgetComponent* HPBarWidgetComp;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Death();
	
};
