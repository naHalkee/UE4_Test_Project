#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

AMyProjectGameMode::AMyProjectGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	AActor* character = UGameplayStatics::GetActorOfClass(GetWorld(), AMyProjectCharacter::StaticClass());

	TArray<AActor*> allAIPlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPlayer::StaticClass(), allAIPlayerActors);
	for (AActor* item : allAIPlayerActors)
	{
		AAIPlayer* aiPlayer = Cast<AAIPlayer>(item);
		aiPlayer->SetCharacter(character);
		allPlayers.Add(aiPlayer);
	}
}

void AMyProjectGameMode::BroadcastToyDestroyed()
{
	OnToyDestroyed.Broadcast();
}

void AMyProjectGameMode::BroadcastToyAvailable(AActor* toy)
{
	AAIPlayer* slowest = nullptr;
	float maxTime = 0;
	for (AAIPlayer* item : allPlayers)
	{
		if (!IsValid(item)) continue;
		item->SetMovementLock(false);
		float otherTime = item->GetTimeToTarget(toy);
		if (maxTime < otherTime)
		{
			maxTime = otherTime;
			slowest = item;
		}
	}
	if (IsValid(slowest)) slowest->SetMovementLock(true);

	OnToyAvailable.Broadcast(toy);
}
