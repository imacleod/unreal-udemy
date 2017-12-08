#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // Must be last include

// Forward declarations
class UTankAimingComponent;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	/// Move tank barrel towards crosshair
	virtual void AimTowardsCrosshair();

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	virtual void SetPawn(APawn* InPawn) override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

	UFUNCTION() // Must be UFUNCTION to be called
	void OnDeath();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
