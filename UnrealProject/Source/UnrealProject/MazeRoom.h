// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <random>

#include "MazeRoom.generated.h"

class AUnrealProjectGameMode;
UCLASS()
class UNREALPROJECT_API UMazeRoom : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UMazeRoom();
	~UMazeRoom();

	void	SetWalls(AUnrealProjectGameMode* Mode, int* Walls, int Height, int Width);

	bool	GenerateRoom();

protected:
	AUnrealProjectGameMode* GameMode = nullptr;

	int* RoomWalls;

	int RoomHeight;
	int RoomWidth;

	int	CurrentX = -1;
	int	CurrentY = -1;

	static std::random_device Rd;
	static std::mt19937 Gen;
};
