#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 HealthMax = 100;

	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 HealthCurrent = HealthMax;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 HealthMin = 0;

public:
	// Return current health as percentage of max health, between 0 and 1
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

	// Called by engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
