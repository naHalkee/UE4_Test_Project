// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UENUM(BlueprintType)
enum class EState : uint8
{
	NotAvailable,
	Available,
};
UCLASS()
class MYPROJECT_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TargetMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CollectionPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EState State = EState::NotAvailable;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
