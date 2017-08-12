
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

	virtual bool GetSightRayHitLocation( FVector& OutHitLocation ) const;
	
public:
	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;

	virtual void Tick( float DeltaSeconds ) override;
};
