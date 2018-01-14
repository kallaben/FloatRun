#pragma once
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOATRUN_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();
	bool IsJumping = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Throw();

private:
	float Reach = 200.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	int ThrowPower = 3000;

	void Grab();
	void Release();
	//Checks if Physics Handle is available.
	void FindPhysicsHandleComponent();
	//Sets up input component for grabbing function
	void SetupInputComponent();
	//Gets start and end of Line Trace with set range.
	FVector GetReachLineEnd();
	FVector GetReachLineStart();
	const FHitResult GetFirstPhysicsBodyInReach();

};