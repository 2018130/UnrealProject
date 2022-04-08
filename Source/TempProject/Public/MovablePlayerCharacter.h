// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovableCharacter.h"
#include "MovablePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPROJECT_API AMovablePlayerCharacter : public AMovableCharacter
{
	GENERATED_BODY()

protected:

	AMovablePlayerCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
		float LagSpeed;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
		class UTimerComponent* TimerComponent;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
};
