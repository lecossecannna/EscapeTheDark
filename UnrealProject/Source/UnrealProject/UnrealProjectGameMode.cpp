// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProjectGameMode.h"

#include <string>

#include "MazeModule.h"
#include "UnrealProjectHUD.h"
#include "UObject/ConstructorHelpers.h"

AUnrealProjectGameMode::AUnrealProjectGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealProjectHUD::StaticClass();

    LineModule = AMazeModule::StaticClass();

    Grid = new int[Width * Height];
}

AUnrealProjectGameMode::~AUnrealProjectGameMode()
{
    delete[] Grid;
}

void AUnrealProjectGameMode::BeginPlay()
{
    GenerateMaze();
    CreateModules();
}

void AUnrealProjectGameMode::GenerateMaze()
{
    srand(time(nullptr));
    ResetGrid();
    Visit(1, 1);
}

void AUnrealProjectGameMode::CreateModules()
{
    for(int iHeight = 0; iHeight < Height; iHeight++)
    {
        for(int jWidth = 0; jWidth < Width; jWidth++)
        {
            if(Grid[XYToIndex(jWidth, iHeight)] == 0)
            {
                FActorSpawnParameters SpawnParameters;
                SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                const FTransform Transform(FRotator::ZeroRotator, FVector{ MazeX + jWidth * ModuleSize, MazeY + iHeight * ModuleSize, 0 });

                GetWorld()->SpawnActor(LineModule, &Transform, SpawnParameters);
            }
        }
    }
}

void AUnrealProjectGameMode::ResetGrid() const
{
    // Fills the grid with walls ('1' characters).
    for (int i=0; i < Width * Height; ++i)
    {
        Grid[i] = 1;
    }
}

int AUnrealProjectGameMode::XYToIndex(int x, int y) const
{
    return y * Width + x;
}

int AUnrealProjectGameMode::IsInBounds(int x, int y) const
{
    if (x < 0 || x >= Width)
        return false;

    if (y < 0 || y >= Height)
        return false;

    return true;
}

void AUnrealProjectGameMode::Visit(int x, int y) const
{
    // Starting at the given index, recursively visits every direction in a
    // randomized order.
    // Set my current location to be an empty passage.
    Grid[ XYToIndex(x,y) ] = 0;

    // Create an local array containing the 4 directions and shuffle their order.
    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;
    for (int i=0; i<4; ++i)
    {
        const int r = rand() & 3;
        const int temp = dirs[r];
        dirs[r]  = dirs[i];
        dirs[i]  = temp;
    }
    // Loop through every direction and attempt to Visit that direction.
    for (int i = 0; i < 4; ++i)
    {
        // dx,dy are offsets from current location.  Set them based
        // on the next direction I wish to try.
        int dx = 0, dy = 0;
        switch (dirs[i])
        {
        case NORTH:
            dy = -1;
            break;
        case SOUTH:
            dy = 1;
            break;
        case EAST:
            dx = 1;
            break;

        case WEST:
            dx = -1;
            break;
        default:
            break;
        }

        // Find the (x,y) coordinates of the grid cell 2 spots
        // away in the given direction.
        const int x2 = x + (dx << 1);
        const int y2 = y + (dy << 1);
        if (IsInBounds(x2, y2))
        {
            if (Grid[XYToIndex(x2, y2)] == 1)
            {
                // (x2,y2) has not been visited yet...knock down the
                // wall between my current position and that position
                Grid[XYToIndex(x2 - dx, y2 - dy)] = 0;
                // Recursively Visit (x2,y2)
                Visit(x2, y2);
            }
        }
    }

    for(int i = 1; i < Height - 1; i+=2)
    {
        for(int j = 1; j < Width - 1; j+=2)
        {
            if(NumberOfWalls(i, j) == 3)
            {
                BreakDeadEndWall(j, i);
            }
        }
    }
}

int AUnrealProjectGameMode::NumberOfWalls(const int x, const int y) const
{
    int WallsCount = 0;

    if(Grid[XYToIndex(x - 1, y)] == 1)
    {
        WallsCount++;
    }

    if (Grid[XYToIndex(x + 1, y)] == 1)
    {
        WallsCount++;
    }

    if (Grid[XYToIndex(x, y - 1)] == 1)
    {
        WallsCount++;
    }

    if (Grid[XYToIndex(x, y + 1)] == 1)
    {
        WallsCount++;
    }

    return WallsCount;
}

void AUnrealProjectGameMode::BreakDeadEndWall(const int x, const int y) const
{
    if (Grid[XYToIndex(x - 1, y)] == 0)
    {
        BreakWall(x + 1, y);
    }
    else if (Grid[XYToIndex(x + 1, y)] == 0)
    {
        BreakWall(x - 1, y);
    }
    else if (Grid[XYToIndex(x, y - 1)] == 0)
    {
        BreakWall(x, y + 1);
    }
    else if (Grid[XYToIndex(x, y + 1)] == 0)
    {
        BreakWall(x, y - 1);
    }
}

void AUnrealProjectGameMode::BreakWall(const int x, const int y) const
{
    if(x == 0 || y == 0 || x == Width || y == Height)
    {
        return;
    }

    Grid[XYToIndex(x, y)] = 0;
}

