#pragma once

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

	UFUNCTION() // Must be UFUNCTION to be called
	void OnPossessedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	// AI tank stops within AcceptanceRadius cm of player
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float AcceptanceRadius = 8000;
};
