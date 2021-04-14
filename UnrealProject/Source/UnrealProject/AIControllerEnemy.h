// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API AAIControllerEnemy : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = EnemyAI)
		class UBehaviorTree* EnemyBehavior = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = EnemyAI)
		FName TargetTag = "Player";
	
};
