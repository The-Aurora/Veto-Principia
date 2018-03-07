// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CirclePlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPosition);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VETOPRINCIPIA_API UCirclePlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCirclePlatform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		float GetLocationX();

	UFUNCTION(BlueprintCallable)
		float GetLocationY();

	UFUNCTION(BlueprintCallable)
		float GetLocationZ();

private:
	AActor* Actor = GetOwner();

	float locationX;
	float locationY;
	float locationZ;

	UPROPERTY(BlueprintAssignable)
		FPosition PositionOne;

	UPROPERTY(BlueprintAssignable)
		FPosition PositionTwo;

	UPROPERTY(BlueprintAssignable)
		FPosition PositionThree;

	UPROPERTY(BlueprintAssignable)
		FPosition PositionFour;

	void OutOfBoundsException();
	bool BOutOfBoundsException = false;
};
