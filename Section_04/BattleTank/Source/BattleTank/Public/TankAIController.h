
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

public:
	virtual void BeginPlay() override;
	
	ATank* GetControlledTank() const;
};
