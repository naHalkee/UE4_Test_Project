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
	ATarget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* TargetMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 CollectionPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EState State = EState::NotAvailable;
};
