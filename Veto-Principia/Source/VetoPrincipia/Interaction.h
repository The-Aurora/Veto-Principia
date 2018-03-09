// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components/InputComponent.h" 
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API UInteraction : public UActorComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static FHitResult GetInteractionResult();

private:
	
	// Find a attached Physics Handle to owner
	void FindAndSetup_InputComponent();

	UInputComponent* InputComponent = nullptr;

	//* Does not return anything, sets ActorInteractedWith declared in Interaction.h upon interaction
	void Interaction();

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	float InteractionReach = 550.f;

	static FHitResult ActorInteractedWith;
};
