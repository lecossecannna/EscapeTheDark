// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALPROJECT_API LogicItens
{
public:
	LogicItens();
	~LogicItens();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ConditionWin)
	TArray<int> ItensConditionWin;
};
