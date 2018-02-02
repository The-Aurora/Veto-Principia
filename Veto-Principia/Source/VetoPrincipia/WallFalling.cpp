// Fill out your copyright notice in the Description page of Project Settings.

#include "WallFalling.h"


// Sets default values for this component's properties
UWallFalling::UWallFalling()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallFalling::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerVolume_Open)
	{
		UE_LOG(LogTemp, Warning, TEXT("(WallFalling.cpp) TriggerVolume_Open failed to be assigned to an actor, please check %s"), *GetOwner()->GetName())
		return;
	}

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UWallFalling::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!TriggerVolume_Open) { return; }

	if (TriggerVolume_Open->IsOverlappingActor(Player)) { Open.Broadcast(); }
}

