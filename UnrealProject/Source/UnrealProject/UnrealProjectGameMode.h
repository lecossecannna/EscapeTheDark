// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealProjectGameMode.generated.h"

#define NORTH	0
#define SOUTH	1
#define WEST	2
#define EAST	3

UCLASS(minimalapi)
class AUnrealProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealProjectGameMode();
	~AUnrealProjectGameMode();

	virtual void BeginPlay() override;

    /**
	 * Should be called only once.
	 */
	void	GenerateMaze();

	float	GetModuleSize() const { return ModuleSize; }

protected:
	void	CreateModules();

	void	ResetGrid() const;
    int		XYToIndex(int x, int y) const;
    int		IsInBounds(int x, int y) const;
    void	Visit(int x, int y) const;

	int		NumberOfWalls(int x, int y) const;
	void	BreakDeadEndWall(int x, int y) const;
	void	BreakWall(int x, int y) const;

	int* Grid;

    /**
	 * Maze's width measured in number of modules.
	 */
	UPROPERTY(EditAnywhere)
	int	Width = 250;

    /**
	 * Maze's height measured in number of modules.
	 */
	UPROPERTY(EditAnywhere)
	int	Height = 250;

    /**
	 * Maze bottom left corner X coordinate.
	 */
	UPROPERTY(EditAnywhere)
	float	MazeX = 0.f;

	/**
	 * Maze bottom left corner Y coordinate.
	 */
	UPROPERTY(EditAnywhere)
	float	MazeY = 0.f;

    /**
	 * X and Y size of modules.
	 */
	UPROPERTY(EditAnywhere)
	int	ModuleSize = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMazeModule> LineModule = nullptr;

};



