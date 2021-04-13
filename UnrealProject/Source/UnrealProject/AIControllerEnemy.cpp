// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerEnemy.h"

#include "UnrealProjectCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIControllerEnemy::BeginPlay()
{
	bool Success = RunBehaviorTree(EnemyBehavior);
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Behavior Tree could not run"));
		return;
	}
	GetBlackboardComponent()->SetValueAsObject(FName("PlayerRef"), GetWorld()->GetFirstPlayerController()->GetPawn());

}

AAIControllerEnemy::AAIControllerEnemy()
{
	
}
