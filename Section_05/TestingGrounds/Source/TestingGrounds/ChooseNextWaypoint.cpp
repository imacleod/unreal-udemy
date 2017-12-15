#include "TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChooseNextWaypoint.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto CurrentIndex = BlackboardComp->GetValueAsInt(IndexSelector.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("CurrentIndex: %i"), CurrentIndex);
	return EBTNodeResult::Succeeded;
}
