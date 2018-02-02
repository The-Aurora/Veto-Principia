// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h" 
#include "Runtime/Engine/Classes/Engine/World.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallFalling.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API UWallFalling : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallFalling();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* Player = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* TriggerVolume_Open = nullptr;
	
	UPROPERTY(BlueprintAssignable)
		FTriggerEvent Open;
};
