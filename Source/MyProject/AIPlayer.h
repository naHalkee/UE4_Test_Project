// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyProjectCharacter.h"
#include "AIPlayer.generated.h"

UCLASS()
class MYPROJECT_API AAIPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentScore;

	UFUNCTION()
	float GetTimeToTarget();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToTarget(float DeltaTime);

	void LookToPlayer();

	UPROPERTY()
	AMyProjectCharacter* character;

	UPROPERTY()
	TArray<AAIPlayer*> otherPlayers;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
