// Fill out your copyright notice in the Description page of Project Settings.

#include "LivesCount.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define OUT

// Called on spawn of the widget
ULivesCount::ULivesCount(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	Super::Construct();

	Lives = 3;
	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Checkpoint"), OUT FoundActors);
		for (AActor* CurrentActor : FoundActors)
		{
			if (CurrentActor->GetName() == TEXT("CheckpointS0201"))
			{
				CheckpointS0201_Location = CurrentActor->GetActorLocation();
				CurrentActor->Destroy();
			}
			if (CurrentActor->GetName() == TEXT("CheckpointS0201_TriggerVol"))
			{
				CheckpointS0201_TriggerVol = CurrentActor;
			}
		}

	}
}

// Ticks every frame
void ULivesCount::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!PlayerCharacter) { return; }


	TArray<AActor*> OverlappingActors;
	CheckpointS0201_TriggerVol->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* CurrentActor : OverlappingActors)
	{
		if (CurrentActor == PlayerCharacter)
		{
			PlayerCharacter->SetActorLocation(CheckpointS0201_Location);
			Lives--;
			if (Lives == 0) 
			{ 
				//Lives = 3;
				UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
			}
		}
	}
}
