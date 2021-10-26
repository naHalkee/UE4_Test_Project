#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIPlayer.h"
#include "MyProjectGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToyAvailable, AActor*, Toy);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToyDestroyed);

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();

	UPROPERTY()
		FToyAvailable OnToyAvailable;

	UPROPERTY()
		FToyDestroyed OnToyDestroyed;

	UFUNCTION(BlueprintCallable)
		void BroadcastToyDestroyed();

	UFUNCTION(BlueprintCallable)
		void BroadcastToyAvailable(AActor* toy);
protected:
	UFUNCTION()
		virtual void BeginPlay() override;

	UPROPERTY()
		TArray<AAIPlayer*> allPlayers;
};



