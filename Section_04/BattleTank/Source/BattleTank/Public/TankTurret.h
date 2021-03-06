#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MaxDegreesPerSecond = 25;
	
public:
	// -1 is min downward speed, +1 is max
	void Rotate(float RelativeSpeed);
};
