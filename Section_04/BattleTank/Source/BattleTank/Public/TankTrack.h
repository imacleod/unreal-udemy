#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack used to set max driving force and apply force to tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UTankTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

	float CurrentThrottle = 0;

	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Sets throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);

	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // Assume 40 ton tank and 1g acceleration
};
