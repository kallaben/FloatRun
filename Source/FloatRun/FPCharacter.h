// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

UCLASS()
class FLOATRUN_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool IsSprinting = false;
public:
	// Sets default values for this character's properties
	AFPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ToggleSprintTrue();

	void ToggleSprintFalse();

	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveLeft(float Value);

	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

};
