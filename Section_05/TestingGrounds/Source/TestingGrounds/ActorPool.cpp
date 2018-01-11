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
	// Same behavior as Return
	if (ActorToAdd == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s - Add() %s"), *GetName(), *ActorToAdd->GetName());
	Return(ActorToAdd);
}

AActor* UActorPool::Checkout()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - Checkout()"), *GetName());
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	if (ActorToReturn == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s - Return() %s"), *GetName(), *ActorToReturn->GetName());
}
