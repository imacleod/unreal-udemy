#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* CollisionMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float DestroyDelay = 3;

	UPROPERTY(VisibleAnywhere, Category="Components")
	URadialForceComponent* ExplosionForceComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UParticleSystemComponent* ImpactBlastComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UParticleSystemComponent* LaunchBlastComponent = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float ProjectileDamage = 20;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float Speed);
};
