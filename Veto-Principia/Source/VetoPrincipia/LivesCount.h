// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LivesCount.generated.h"

UCLASS()
class VETOPRINCIPIA_API ULivesCount : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Constructor
	ULivesCount(const FObjectInitializer& ObjectInitializer);

	// Ticks every frame
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:


	
private:

	AActor* PlayerCharacter;
	FVector CheckpointS0201_Location;
	AActor* CheckpointS0201_TriggerVol;
	uint8 Lives;
};
