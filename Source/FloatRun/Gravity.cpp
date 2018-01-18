// Fill out your copyright notice in the Description page of Project Settings.

#include "Gravity.h"


// Sets default values for this component's properties
UGravity::UGravity()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravity::BeginPlay()
{
	Super::BeginPlay();
	PrimComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();

	// ...
	
}


// Called every frame
void UGravity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (EnableGravity)
	{
		PrimComponent->AddForce(FVector(0.0f, 0.0f, GravityZ));
	}

	// ...
}

