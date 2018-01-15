#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	AActor* NavMeshBoundsVolume;

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	// AI pawn
	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

	UActorPool* Pool;

	void PositionNavMeshBoundsVolume();

	template<class ActorType>
	void RandomlyPlaceActors(TSubclassOf<ActorType> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category="Navigation")
	FVector MinSpawnExtent;

	UPROPERTY(EditDefaultsOnly, Category="Navigation")
	FVector MaxSpawnExtent;

	UPROPERTY(EditDefaultsOnly, Category="Navigation")
	FVector NavigationBoundsOffset;

public:	
	// Sets default values for this actor's properties
	ATile();

	// Randomly generate and place level/tile props
	UFUNCTION(BlueprintCallable, Category="Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn=1, int MaxSpawn=1, float Radius=500, float MinScale=1, float MaxScale=1);

	// Randomly generate and place AI
	UFUNCTION(BlueprintCallable, Category="Setup")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn=1, int MaxSpawn=1, float Radius=500);

	UFUNCTION(BlueprintCallable, Category="Pool")
	void SetPool(UActorPool* ActorPool);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
