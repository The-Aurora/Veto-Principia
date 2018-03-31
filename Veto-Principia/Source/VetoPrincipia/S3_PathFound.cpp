// Fill out your copyright notice in the Description page of Project Settings.

#include "S3_PathFound.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#define OUT

// Sets default values for this component's properties
US3_PathFound::US3_PathFound()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void US3_PathFound::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() || GetWorld()->GetFirstPlayerController())
	{
		PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}


// Called every frame
void US3_PathFound::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter && TriggerVolume)
	{
		TArray<AActor*> OverlappingActors;
		TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

		for (AActor* CurrentActor : OverlappingActors)
		{
			if (CurrentActor == PlayerCharacter)
			{
				DestroyRequest.Broadcast();
			}
		}
	}

}

