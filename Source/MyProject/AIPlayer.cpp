// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayer.h"
#include <Kismet/KismetMathLibrary.h>


// Sets default values
AAIPlayer::AAIPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AAIPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (Speed == 0)
	{
		Speed = FMath::RandRange(100, 300);
	}
	character = (AMyProjectCharacter*)UGameplayStatics::GetActorOfClass(GetWorld(), AMyProjectCharacter::StaticClass());
	TArray<AActor*> allAIPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPlayer::StaticClass(), allAIPlayers);
	for (AActor* item : allAIPlayers)
	{
		AAIPlayer* aiPlayer = Cast<AAIPlayer>(item);
		if (aiPlayer != this) otherPlayers.Add(aiPlayer);
	}
}

float AAIPlayer::GetTimeToTarget()
{
	if (character != nullptr && character->CurrentToy != nullptr)
	{
		FVector direction = character->CurrentToy->GetActorLocation() - GetActorLocation();
		return direction.Size() / Speed;
	}
	return 0.f;
}

void AAIPlayer::MoveToTarget(float DeltaTime)
{
	FVector direction = character->CurrentToy->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	direction.Normalize();
	SetActorLocation(GetActorLocation() + direction * DeltaTime * Speed);

	FRotator rotator = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(rotator);
}

void AAIPlayer::LookToPlayer()
{
	FVector direction = character->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	FRotator rotator = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(rotator);
}

// Called every frame
void AAIPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (character != nullptr)
	{
		if (character->CurrentToy != nullptr && character->CurrentToy->State == EState::Available)
		{
			float maxTime = 0;
			for (AAIPlayer* item : otherPlayers)
			{
				if (item == nullptr) continue;
				float otherTime = item->GetTimeToTarget();
				if (maxTime < otherTime)
				{
					maxTime = otherTime;
				}
			}
			if (GetTimeToTarget() >= maxTime)
			{
				LookToPlayer();
			}
			else
			{
				MoveToTarget(DeltaTime);
			}
		}
		else
		{
			LookToPlayer();
		}
	}
}

