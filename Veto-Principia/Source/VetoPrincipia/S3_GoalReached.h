// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include"Runtime/Engine/Classes/Engine/TriggerVolume.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S3_GoalReached.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API US3_GoalReached : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	US3_GoalReached();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//* Check whether the goal has been reached, if true the function broadcasts into BP
	void CheckForGoalStatus();

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerVolume = nullptr;

	UPROPERTY(BlueprintAssignable)
		FCustomEvent ElevatePlatform;

};
