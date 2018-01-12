#include "TestingGrounds.h"
#include "Tile.h"
#include "ActorPool.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxSpawnExtent = FVector(4000, 2000, 0);
	MinSpawnExtent = FVector(0, -2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);
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
	FBox Bounds(MinSpawnExtent, MaxSpawnExtent);

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
void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));  // Don't weld when simulating physics
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s - not enough actors in pool!"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s checked out %s"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions;
	int32 NumSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool ValidLocation = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);

		if (ValidLocation)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositions.Add(SpawnPosition);
		}
	}
	return SpawnPositions;
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
