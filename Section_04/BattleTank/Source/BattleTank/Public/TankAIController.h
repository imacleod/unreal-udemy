
#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"  // Must be last include


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
};
