// Fill out your copyright notice in the Description page of Project Settings.


#include "LogicItens.h"

LogicItens::LogicItens()
{
	ItensConditionWin.Add(FMath::RandRange(0, 5));

	int SecondItem = FMath::RandRange(0, 5);
	while(SecondItem == ItensConditionWin[0])
	{
		SecondItem = FMath::RandRange(0, 5);
	}

	ItensConditionWin.Add(SecondItem);

	bool FoundUniqueThirdItem = false;
	int ThirdItem = FMath::RandRange(0, 5);
	while(!FoundUniqueThirdItem)
	{
	    if(ThirdItem != ItensConditionWin[0] && ThirdItem != ItensConditionWin[1])
	    {
			FoundUniqueThirdItem = true;
	    }
		else
		{
			ThirdItem = FMath::RandRange(0, 5);
		}
	}

	ItensConditionWin.Add(ThirdItem);
}

LogicItens::~LogicItens()
{
}
