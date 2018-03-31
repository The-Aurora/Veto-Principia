// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S3_PathFound.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerVolumeOverlapped);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API US3_PathFound : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	US3_PathFound();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private: 

	AActor* PlayerCharacter;

	UPROPERTY(EditAnywhere)
		AActor* TriggerVolume;

	UPROPERTY(BlueprintAssignable)
		FTriggerVolumeOverlapped DestroyRequest;
	
};
