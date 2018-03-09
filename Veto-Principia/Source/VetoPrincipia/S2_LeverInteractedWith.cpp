// Fill out your copyright notice in the Description page of Project Settings.

#include "S2_LeverInteractedWith.h"
#include "Interaction.h"

// Sets default values for this component's properties
US2_LeverInteractedWith::US2_LeverInteractedWith()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void US2_LeverInteractedWith::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void US2_LeverInteractedWith::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* ActorHit = UInteraction::GetInteractionResult().GetActor();

	if (ActorHit && InteractionActor)
	{
		if (InteractionActor->GetName() == ActorHit->GetName())
		{
			TriggerEvent.Broadcast();
		}
		
	}
}