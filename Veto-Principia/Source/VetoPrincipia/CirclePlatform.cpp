// Fill out your copyright notice in the Description page of Project Settings.

#include "CirclePlatform.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values for this component's properties
UCirclePlatform::UCirclePlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCirclePlatform::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the values
	locationX = GetOwner()->GetActorLocation().X;
	locationY = GetOwner()->GetActorLocation().Y;
	locationZ = GetOwner()->GetActorLocation().Z;
}


// Called every frame
void UCirclePlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Determines whether the actor is located within the following ranges to broadcast into BP and set helper values
	// Position One
	if (GetOwner()->GetActorLocation().X == -5337.0 && GetOwner()->GetActorLocation().Y == -3760.0)
	{
		locationX = -5337.0;
		locationY = -3760.0;
		locationZ = 15.0;
		PositionOne.Broadcast();
	}

	// Position Two
	else if (GetOwner()->GetActorLocation().X == -2232.0 && GetOwner()->GetActorLocation().Y == -3760.0)
	{
		locationX = -2232.0;
		locationY = -3760.0;
		locationZ = 15.0;
		PositionTwo.Broadcast();
	}
	
	// Position Three
	else if (GetOwner()->GetActorLocation().X == -2232.0 && GetOwner()->GetActorLocation().Y == -6930.0)
	{
		locationX = -2232.0;
		locationY = -6930.0;
		locationZ = 15.0;
		PositionThree.Broadcast();
	}

	// Position Four
	else if (GetOwner()->GetActorLocation().X == -5337.0 && GetOwner()->GetActorLocation().Y == -6930.0)
	{
		locationX = -5337.0;
		locationY = -6930.0;
		locationZ = 15.0;
		PositionFour.Broadcast();
	}

	//TODO:Finish a fix if this happens
	// If the actor is not found within the parameters
	//OutOfBoundsException();
}

float UCirclePlatform::GetLocationX()
{
	return locationX;
}

float UCirclePlatform::GetLocationY()
{
	return locationY;
}

float UCirclePlatform::GetLocationZ()
{
	return locationZ;
}

void UCirclePlatform::OutOfBoundsException()
{
	if (BOutOfBoundsException == false)
	{
		BOutOfBoundsException = true;
		UE_LOG(LogTemp, Error, TEXT("(CirclePlatform.cpp(56)) Platform '%s' is out of bounds."), *GetOwner()->GetName());
	}
}