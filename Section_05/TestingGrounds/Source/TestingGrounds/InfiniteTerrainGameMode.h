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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pool")
	class UActorPool* NavMeshBoundsVolumePool;

public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category="Pool")
	void PopulateBoundsVolumePool();
};
