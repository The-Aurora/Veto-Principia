// Fill out your copyright notice in the Description page of Project Settings.

#include "S3_GoalReached.h"

#define OUT

// Sets default values for this component's properties
US3_GoalReached::US3_GoalReached()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void US3_GoalReached::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void US3_GoalReached::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForGoalStatus();
}

//* Check whether the goal has been reached, if true the function broadcasts into BP
void US3_GoalReached::CheckForGoalStatus()
{
	if (!TriggerVolume) { return; }

	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (const AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			ElevatePlatform.Broadcast();
		}
	}
}
