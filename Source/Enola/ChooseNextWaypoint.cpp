// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO: Protect against empty patrolroute component.


	
	// TODO: check null values empty routes
	
	// get the patrol points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Warn if empty patrolroutes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if(PatrolPoints.Num() == 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PatrolPoints missing"))
		return EBTNodeResult::Failed;
	}
	

	// Get Blackboard component from the owner component.
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	// Get current waypoint index, by key.
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	// Set next waypoint
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	

	// Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
		
	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index : %i"), NextIndex);

	return EBTNodeResult::Succeeded;
}