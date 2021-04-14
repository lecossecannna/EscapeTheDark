// Fill out your copyright notice in the Description page of Project Settings.


#include "LogicItens.h"

LogicItens::LogicItens()
{
	ItensConditionWin.Add(FMath::RandRange(0, 6));
	ItensConditionWin.Add(FMath::RandRange(0, 6));
	ItensConditionWin.Add(FMath::RandRange(0, 6));
}

LogicItens::~LogicItens()
{
}
