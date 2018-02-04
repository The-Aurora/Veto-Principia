// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/// IWYU
#include"Runtime/Engine/Classes/Engine/TriggerVolume.h" 

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Entr_ItemDeposited.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMassReachedStatus);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API UEntr_ItemDeposited : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntr_ItemDeposited();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float GetMassInBox();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	AActor* Object = nullptr;

	UPROPERTY(EditAnywhere)
		float MassToOpen = 5.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* BoxTriggerVolume = nullptr;

	UPROPERTY(BlueprintAssignable)
		FMassReachedStatus OpenRequest;
};
