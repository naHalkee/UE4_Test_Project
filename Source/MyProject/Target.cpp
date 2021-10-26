#include "Target.h"

ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;
	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>("TargetMesh");
}
