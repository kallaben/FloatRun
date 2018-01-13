// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCharacter.h"


// Sets default values
AFPCharacter::AFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("FPCharacter is in play."));
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AFPCharacter::MoveLeft);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPCharacter::ToggleSprintTrue);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPCharacter::ToggleSprintFalse);

	// Mouse bindings
	PlayerInputComponent->BindAxis("Turn", this, &AFPCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPCharacter::AddControllerPitchInput);

	//Jump bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPCharacter::StopJump);
}

void AFPCharacter::ToggleSprintTrue()
{
	UE_LOG(LogTemp, Warning, TEXT("Sprint: True."));
	IsSprinting = true;
}

void AFPCharacter::ToggleSprintFalse()
{
	UE_LOG(LogTemp, Warning, TEXT("Sprint: False."));
	IsSprinting = false;
}

void AFPCharacter::MoveForward(float Value)
{
	// Get vector that defines players rotation on the x-axis
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	IsSprinting ? AddMovementInput(Direction, Value) : AddMovementInput(Direction, Value * 0.5);
}

void AFPCharacter::MoveLeft(float Value)
{
	// Get vector that defines players rotation on the x-axis
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	IsSprinting ? AddMovementInput(Direction, Value) : AddMovementInput(Direction, Value * 0.5);
}

void AFPCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPCharacter::StopJump()
{
	bPressedJump = false;
}
