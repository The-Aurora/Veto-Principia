// Fill out your copyright notice in the Description page of Project Settings.

#include "Interaction.h"
FHitResult UInteraction::ActorInteractedWith = FHitResult();

#define OUTPUT

// Sets default values for this component's properties
UInteraction::UInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteraction::BeginPlay()
{
	Super::BeginPlay();

	FindAndSetup_InputComponent();

	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("(Interaction.cpp) InputComponent failed to get assigned. On: %s"), *GetOwner()->GetName());
		return;
	}
}


// Called every frame
void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Stores Viepoint Location+Rotation into values defined in .h and calculates the length of line trace
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUTPUT PlayerViewpointLocation,
		OUTPUT PlayerViewpointRotation
	);
}

//* Find a attached Input Component to owner and bind inputs
void UInteraction::FindAndSetup_InputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &UInteraction::Interaction);
	}
}

//* Does not return anything, sets ActorInteractedWith declared in Interaction.h upon interaction
void UInteraction::Interaction()
{
	FVector PlayerVPLineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * InteractionReach;

	/// Setup query paramaters 
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line-trace (ray-casting) out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUTPUT ActorInteractedWith,
		PlayerViewpointLocation,
		PlayerVPLineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
}

//* Gets FHitResult of the actor interacted with
FHitResult UInteraction::GetInteractionResult()
{
	return ActorInteractedWith;
}