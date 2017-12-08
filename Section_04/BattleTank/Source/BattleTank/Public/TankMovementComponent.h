#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;


/**
 * Responsible for driving tank tracks
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Called by pathfinding in AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

public:
	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category="Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category="Input")
	void IntendTurnRight(float Throw);
};
