// Fill out your copyright notice in the Description page of Project Settings.

#include "Dash.h"


// Sets default values for this component's properties
UDash::UDash()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDash::BeginPlay()
{
	Super::BeginPlay();

	//Get owner
	Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("No actor found for Dash component."));
	}

	//Get physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No phyics component found for %s."), *GetOwner()->GetName());
	}

	GetGrabber();

	ComponentToDash = Owner->FindComponentByClass<UPrimitiveComponent>();

	UE_LOG(LogTemp, Error, TEXT("Owner of prim component: %s"), *ComponentToDash->GetOwner()->GetName());

	SetupInputComponent();
}


// Called every frame
void UDash::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//Get grabber for "IsJumping" value
void UDash::GetGrabber()
{
	Grabber = Owner->FindComponentByClass<UGrabber>();
	if (Grabber == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No grabber component found."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber component found."));
	}
}

//Setting up input
void UDash::SetupInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();
	//Dash bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &UDash::Dash);
}

void UDash::Dash()
{
	if (Grabber->IsJumping)
	{
		UE_LOG(LogTemp, Error, TEXT("Dash succesful!"));
		APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

		FVector camLocation = camManager->GetCameraLocation();
		FVector camForward = camManager->GetCameraRotation().Vector();

		ComponentToDash->AddImpulse((camForward * DashPower), NAME_None, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Dash unsuccesful!"));
		return;
	}
}
