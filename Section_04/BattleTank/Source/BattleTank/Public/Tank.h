#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	ATank();

private:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 HealthMax = 100;

	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 HealthCurrent = HealthMax;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 HealthMin = 0;

public:
	// Called by engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
