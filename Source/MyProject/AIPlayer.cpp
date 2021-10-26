#include "AIPlayer.h"
#include <Kismet/KismetMathLibrary.h>
#include "MyProjectGameMode.h"

AAIPlayer::AAIPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (Speed == 0)
	{
		Speed = FMath::RandRange(100, 300);
	}
	AMyProjectGameMode* GameMode = Cast<AMyProjectGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnToyAvailable.AddDynamic(this, &AAIPlayer::OnToyAvailable);
}

float AAIPlayer::GetTimeToTarget(AActor* target)
{
	if (!IsValid(target)) return FLT_MAX;
	FVector direction = target->GetActorLocation() - GetActorLocation();
	return direction.Size() / Speed;
}

void AAIPlayer::SetCharacter(AActor* character)
{
	currentCharacter = character;
}

void AAIPlayer::SetMovementLock(bool state)
{
	movementLocked = state;
}

void AAIPlayer::MoveToTarget(float DeltaTime)
{
	if (!IsValid(currentToy)) return;
	FVector direction = currentToy->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	direction.Normalize();
	SetActorLocation(GetActorLocation() + direction * DeltaTime * Speed);

	FRotator rotator = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(rotator);
}

void AAIPlayer::LookToPlayer()
{
	if (!IsValid(currentCharacter)) return;
	FVector direction = currentCharacter->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	FRotator rotator = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(rotator);
}

void AAIPlayer::OnToyAvailable(AActor* toy)
{
	currentToy = toy;
}

void AAIPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (movementLocked || !IsValid(currentToy))
	{
		LookToPlayer();
	}
	else
	{
		MoveToTarget(DeltaTime);
	}
}

