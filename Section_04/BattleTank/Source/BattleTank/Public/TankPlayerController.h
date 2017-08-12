
#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // Must be last include


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

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	ATank* GetControlledTank() const;

	virtual bool GetSightRayHitLocation( FVector& OutHitLocation ) const;
	
public:
	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;
};
