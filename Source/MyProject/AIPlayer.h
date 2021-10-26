#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPlayer.generated.h"

UCLASS()
class MYPROJECT_API AAIPlayer : public AActor
{
	GENERATED_BODY()

public:
	AAIPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 CurrentScore;

	UFUNCTION()
		float GetTimeToTarget(AActor* target);

	UFUNCTION()
		void SetCharacter(AActor* character);

	UFUNCTION()
		void SetMovementLock(bool state);
protected:
	virtual void BeginPlay() override;

	void MoveToTarget(float DeltaTime);

	void LookToPlayer();

	UFUNCTION()
		void OnToyAvailable(AActor* toy);

	UPROPERTY()
		AActor* currentToy;

	UPROPERTY()
		bool movementLocked;

	UPROPERTY()
		AActor* currentCharacter;
public:
	virtual void Tick(float DeltaTime) override;


};
