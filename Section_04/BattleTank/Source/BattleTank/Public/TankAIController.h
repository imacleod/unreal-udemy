#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"  // Must be last include

class UTankAimingComponent;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	bool bIsPlayerVisible(UTankAimingComponent* AimingComponent);

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	UFUNCTION() // Must be UFUNCTION to be called
	void OnPossessedTankDeath();

	FVector PossessedTankLocation;

	FRotator PossessedTankRotation;

	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void Tick(float DeltaSeconds) override;

	void UpdateViewPoint();

protected:
	// AI tank stops within AcceptanceRadius cm of player
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float AcceptanceRadius = 8000;
};
