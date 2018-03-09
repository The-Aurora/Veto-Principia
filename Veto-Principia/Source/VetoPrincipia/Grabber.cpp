// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#define OUTPUT // clarity macro when function changes parameters

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

	Find_PhysicsHandle();
	FindAndSetup_InputComponent();

	if (!PhysicsHandle || !InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("(Grabber.cpp) PhysicsHandle or InputComponent failed to get assigned. On: %s"), *GetOwner()->GetName());
		return;
	}

}

// Find a attached Physics Handle to owner
void UGrabber::Find_PhysicsHandle()
{
	/// Look for attached (to owner) Physics Handle 
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	/// For diagnostic purposes
	/*if (PhysicsHandle)
	{
	UE_LOG(LogTemp, Warning, TEXT("Physics Handle has been found ! Owner: %s"), *GetOwner()->GetName());
	}
	else
	{
	UE_LOG(LogTemp, Error, TEXT("Error: Physics Handle has not been found. Owner: %s"), *GetOwner()->GetName());
	}*/
}

// Find a attached Input Component to owner
void UGrabber::FindAndSetup_InputComponent()
{
	/// Look for attached (to owner) Input Component 
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// For diagnostic purposes
		//UE_LOG(LogTemp, Warning, TEXT("Input Component has been found ! Owner: %s"), *GetOwner()->GetName());

		/// Bind the input axis 
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Grab_Release);
	}
	else
	{
		/// For diagnostic purposes
		//UE_LOG(LogTemp, Error, TEXT("Error: Input Component has not been found. Owner: %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }

	/// For diagnostic purposes
	/*FVector PlayerVPLineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * GrabReach;
	DrawDebugLine
	(
		GetWorld(),
		PlayerViewpointLocation,
		PlayerVPLineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/

	if (PhysicsHandle->GrabbedComponent)
	{
		GetViewpointLocationAndRotation();
		ObjectNewLocation = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * HoldingReach;
		PhysicsHandle->SetTargetLocation(ObjectNewLocation);
	}
}

// Stores Viepoint Location+Rotation into values defined in .h, DOES NOT RETURN ANYTHING
void UGrabber::GetViewpointLocationAndRotation()
{
	/// Stores Viepoint Location+Rotation into values defined in .h and calculates the length of line trace
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPUT PlayerViewpointLocation,
		OUTPUT PlayerViewpointRotation
	);
}

// Method for grabbing (attaching Physics Handle) with compatible physics channel 
void UGrabber::Grab()
{
	/// For diagnostic purposes
	//UE_LOG(LogTemp, Warning, TEXT("Grab key pressed."));

	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	GetViewpointLocationAndRotation();
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto HitActor = HitResult.GetActor();

	if (HitActor) {
		// attach physics handle
		if (!PhysicsHandle) { return; }

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitActor->GetActorLocation(),
			HitActor->GetActorRotation()
		);
	}
}

// Method for releasing a object attached by Physics Handle
void UGrabber::Grab_Release()
{
	/// For diagnostic purposes
	//UE_LOG(LogTemp, Warning, TEXT("Grab key released."));

	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

// Attempts (ray-casts) to hit a compatible colision channel and returns hit result
FHitResult const UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerVPLineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * GrabReach;

	/// Setup query paramaters 
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line-trace (ray-casting) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUTPUT Hit,
		PlayerViewpointLocation,
		PlayerVPLineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	/// For diagnostic purposes
	/*AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
	UE_LOG(LogTemp, Warning, TEXT("Actor %s has been line trace hit by: %s"), *(ActorHit->GetName()), *(GetOwner()->GetName()));
	}*/

	return Hit;
}