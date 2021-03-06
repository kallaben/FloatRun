// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/ActorComponent.h"
#include "Dash.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOATRUN_API UDash : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDash();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetGrabber();

	void SetupInputComponent();

	void Dash();

private:
	AActor* Owner = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UGrabber* Grabber = nullptr;
	UInputComponent* InputComponent = nullptr;
	UPrimitiveComponent* ComponentToDash = nullptr;

	UPROPERTY(EditAnywhere)
	int DashPower = 300;
};
