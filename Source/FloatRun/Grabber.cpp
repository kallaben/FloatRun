// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "engine/World.h"

//Annotating changed output variables
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();


}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!PhysicsHandle || IsJumping)
	{
		Release();
		return;
	}

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}


}

void UGrabber::AdvanceTimer()
{
	if (CountdownTime == 0)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
	else
	{
		--CountdownTime;
	}
}

void UGrabber::Throw()
{
	if (!PhysicsHandle)
		return;

	CountdownTime = 1;
	GetOwner()->GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &UGrabber::AdvanceTimer, 1.0f, true);

	APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	//Get first moveable object
	auto HitResult = GetFirstPhysicsBodyInReach();
	//Get the primitive component that is grabbable
	auto ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();
	//Throwing function
	if (ActorHit) {
		Release();
		ComponentToGrab->AddImpulse((camForward * ThrowPower), NAME_None, true);	
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//Objects that are being hit
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return HitResult;
}


void UGrabber::Grab(float value) {
	if (!PhysicsHandle)
		return;


	if (value == 0)
	{
		Release();
	}
	else if (PhysicsHandle->GrabbedComponent)
	{
		return;
	}
	else if (CountdownTime <= 0)
	{
		auto HitResult = GetFirstPhysicsBodyInReach();
		auto ComponentToGrab = HitResult.GetComponent();
		auto ActorHit = HitResult.GetActor();

		//Grabbing function
		if (ActorHit) {
			//If body is static before grab, but still has physics enabled.
			ComponentToGrab->GetOwner()->FindComponentByClass<UGravity>()->EnableGravity = true;
			PhysicsHandle->GrabComponent(
				ComponentToGrab,
				NAME_None,
				ComponentToGrab->GetOwner()->GetActorLocation(),
				true);
		}
		return;
	}
	else
	{
		return;
	}
}

void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();
}
//Checks if physics handle is available.
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
		UE_LOG(LogTemp, Error, TEXT("No phyics component found for %s."), *GetOwner()->GetName());
}

//Checks if input component is available.
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAxis("Grab", this, &UGrabber::Grab);
		InputComponent->BindAction("Throw", IE_Pressed, this, &UGrabber::Throw);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("No InputComponent found for %s."), *GetOwner()->GetName());
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLocation, OUT PlayerVPRotation);

	return PlayerVPLocation + (PlayerVPRotation.Vector()*Reach);
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLocation, OUT PlayerVPRotation);

	return PlayerVPLocation;
}