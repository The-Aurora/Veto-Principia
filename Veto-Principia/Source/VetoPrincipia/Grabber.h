// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h" 
#include "Runtime/Engine/Classes/Components/InputComponent.h" 

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	FVector ObjectNewLocation;

	// GrabReach is for when the game attempts to hit an object, HoldingReach is for when the object is being held
	float GrabReach = 550.f;
	float HoldingReach = 400.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Method which stores Viepoint Location+Rotation into values defined in .h, DOES NOT RETURN ANYTHING
	void GetViewpointLocationAndRotation();

	// Method for grabbing (attaching Physics Handle) with compatible physics channel 
	void Grab();

	// Method for releasing a object attached by Physics Handle
	void Grab_Release();

	// Find a attached Physics Handle to owner
	void Find_PhysicsHandle();

	// Find a attached Input Component to owner
	void FindAndSetup_InputComponent();

	// Return hit result for first physics body in reach
	FHitResult const GetFirstPhysicsBodyInReach();
};
