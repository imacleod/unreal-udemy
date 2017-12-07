#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const
{
	return float(HealthCurrent) / float(HealthMax);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	int32 DamageAmountInt = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmountInt, HealthMin, HealthCurrent);

	HealthCurrent -= DamageToApply;
	if (HealthCurrent <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}
