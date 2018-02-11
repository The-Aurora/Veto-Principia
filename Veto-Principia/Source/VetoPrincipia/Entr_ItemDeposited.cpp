// Fill out your copyright notice in the Description page of Project Settings.

#include "Entr_ItemDeposited.h"

///IWYU
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT // clarity macro

// Sets default values for this component's properties
UEntr_ItemDeposited::UEntr_ItemDeposited()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEntr_ItemDeposited::BeginPlay()
{
	Super::BeginPlay();

	Object = GetOwner();

	if (!Object || !BoxTriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("(Entr_ItemDeposited.cpp) Object or BoxTriggerVolume failed to get assigned. On: %s"), *GetOwner()->GetName());
		return;
	}
	
}


// Called every frame
void UEntr_ItemDeposited::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassInBox() >= MassToOpen) { OpenRequest.Broadcast(); }
}


float UEntr_ItemDeposited::GetMassInBox()
{
	// To avoid crash
	if (!BoxTriggerVolume) { return 0.f; }

	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	BoxTriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* OverlappingActor : OverlappingActors)
	{
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Overlapping actor: %s, TotalMass: %s"), *OverlappingActor->GetName(), *FString::SanitizeFloat(TotalMass));
	}

	return TotalMass;
}