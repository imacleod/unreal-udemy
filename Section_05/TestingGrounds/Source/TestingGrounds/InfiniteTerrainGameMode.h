#pragma once

#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);

public:
	UFUNCTION(BlueprintCallable, Category="BoundsPool")
	void PopulateBoundsVolumePool();
};
