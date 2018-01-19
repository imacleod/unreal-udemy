#include "TestingGrounds.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (ActorToAdd == nullptr) { return; }
	Pool.Push(ActorToAdd);
}

AActor* UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{
	// Same behavior as Add 
	if (ActorToReturn == nullptr) { return; }
	Add(ActorToReturn);
}
