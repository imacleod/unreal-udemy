#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"


UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	UAnimInstance* AnimInstance;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class UAnimMontage* FireAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	// Fires a projectile
	UFUNCTION(BlueprintCallable, Category="Setup")
	void OnFire();
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
