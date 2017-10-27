
#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"  // Must be last include

// Forward declarations
class ATank;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;

	virtual void Tick(float DeltaSeconds) override;
};
