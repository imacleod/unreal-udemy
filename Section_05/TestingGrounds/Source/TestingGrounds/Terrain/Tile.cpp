#include "TestingGrounds.h"
#include "Tile.h"
#include "ActorPool.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,  // Our "Spawn" custom trace channel, determined in DefaultEngine.ini
		FCollisionShape::MakeSphere(Radius)
	);

	return !HasHit;
}

// Search for empty location in level/tile that can be used for actor placement
bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	const int MAX_ATTEMPTS = 100;

	// Assuming 4000 x 4000 tile with origin in center of rear barrier
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector RandomLocation = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(RandomLocation, Radius))
		{
			OutLocation = RandomLocation;
			return true;
		}
	}
	return false;
}

// Place actor at location, randomizing rotation and scale
void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));  // Don't weld when simulating physics

	float RandomRotation = FMath::RandRange(-180.f, 180.f);
	Spawned->SetActorRotation(FRotator(0, RandomRotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int32 NumSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool ValidLocation = FindEmptyLocation(SpawnPoint, Radius * RandomScale);

		if (ValidLocation)
		{
			PlaceActor(ToSpawn, SpawnPoint, RandomScale);
		}
	}
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has null nav mesh bounds volume!"), *GetName());
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

void ATile::SetPool(UActorPool* ActorPool)
{
	Pool = ActorPool;

	PositionNavMeshBoundsVolume();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
