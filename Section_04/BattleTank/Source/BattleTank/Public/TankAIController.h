
#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"  // Must be last include

// Forward declarations
class ATank;
class UTankAimingComponent;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// AI tank stops within AcceptanceRadius cm of player
	float AcceptanceRadius = 3000;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};
