// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProjectGameMode.h"


#include <ctime>
#include <string>

#include "MazeModule.h"
#include "MazeRoom.h"
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
    CrossroadsModule = AMazeModule::StaticClass();
    TModule = AMazeModule::StaticClass();

    Grid = new int[Width * Height];

    Rooms.Add(CreateDefaultSubobject<UMazeRoom>(FName("Room0")));
    int Room1[32]{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2, 2, 2, 2 };
    Rooms[0]->SetWalls(this, Room1, 8, 4);

    Rooms.Add(CreateDefaultSubobject<UMazeRoom>(FName("Room1")));
    int Room2[32]{ 0, 0, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2 ,2, 2, 2, 2 };
    Rooms[1]->SetWalls(this, Room2, 8, 4);

    Rooms.Add(CreateDefaultSubobject<UMazeRoom>(FName("Room2")));
    int Room3[32]{ 0, 0, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2 ,2, 2, 2, 2 };
    Rooms[2]->SetWalls(this, Room3, 8, 4);

    Rooms.Add(CreateDefaultSubobject<UMazeRoom>(FName("Room3")));
    int Room4[32]{ 0, 0, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2 ,2, 2, 2, 2 };
    Rooms[3]->SetWalls(this, Room4, 8, 4);

    Rooms.Add(CreateDefaultSubobject<UMazeRoom>(FName("Room4")));
    int Room5[32]{ 0, 0, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2, 2, 2, 2, 2,
                    2, 2, 2, 2 ,2, 2, 2, 2 };
    Rooms[4]->SetWalls(this, Room5, 8, 4);
}

void AUnrealProjectGameMode::BeginPlay()
{
    GenerateMaze();

    auto TempRooms = Rooms;
    for(int i = TempRooms.Num() - 1; i >= 0; i--)
    {
        if(!TempRooms[i]->GenerateRoom())
        {
            TempRooms.RemoveAt(i);
        }
    }

    Rooms = TempRooms;

    //for (auto It = Rooms.begin(); It != Rooms.end(); ++It)
    //{
    //    if (!(*It)->GenerateRoom())
    //    {
    //        Rooms.Remove(*It);
    //        ++It;
    //    }
    //}

    CreateModules();
}

void AUnrealProjectGameMode::GenerateMaze() const
{
    srand(time(nullptr));
    ResetGrid();
    Visit(1, 1);
}

void AUnrealProjectGameMode::CreateModules() const
{
    for(int iHeight = 0; iHeight < Height; iHeight++)
    {
        for(int jWidth = 0; jWidth < Width; jWidth++)
        {
            if (Grid[XYToIndex(jWidth, iHeight)] == GROUND || Grid[XYToIndex(jWidth, iHeight)] == ROOM_GROUND)
            {
                EModuleType ModuleType = static_cast<EModuleType>(Grid[XYToIndex(jWidth, iHeight)]);

                UClass* ModuleClass = nullptr;
                FRotator ModuleRotation = FRotator::ZeroRotator;
                const int WallsCount = NumberOfWalls(jWidth, iHeight, ModuleType);

                if (WallsCount == 2)
                {
                    if (Grid[XYToIndex(jWidth, iHeight - 1)] == Grid[XYToIndex(jWidth, iHeight + 1)]
                        || Grid[XYToIndex(jWidth - 1, iHeight)] == Grid[XYToIndex(jWidth + 1, iHeight)] ) // Line
                    {
                        if (Grid[XYToIndex(jWidth, iHeight + 1)] == ModuleType)
                        {
                            ModuleRotation.Yaw = 90;
                        }

                        ModuleClass = LineModule;
                    }
                    else // Turn
                    {
                        if (Grid[XYToIndex(jWidth, iHeight + 1)] != ModuleType)
                        {
                            if (Grid[XYToIndex(jWidth + 1, iHeight)] != ModuleType)
                            {
                                ModuleRotation.Yaw = 90;
                            }
                            else
                            {
                                ModuleRotation.Yaw = 180;
                            }
                        }
                        else
                        {
                            if (Grid[XYToIndex(jWidth + 1, iHeight)] != ModuleType)
                            {
                                ModuleRotation.Yaw = 0;
                            }
                            else
                            {
                                ModuleRotation.Yaw = -90;
                            }
                        }
                        ModuleClass = TurnModule;
                    }
                }
                else if (WallsCount == 1) // T
                {
                    if (Grid[XYToIndex(jWidth, iHeight - 1)] != ModuleType)
                    {
                        ModuleRotation.Yaw = -90;
                    }
                    else if (Grid[XYToIndex(jWidth, iHeight + 1)] != ModuleType)
                    {
                        ModuleRotation.Yaw = 90;
                    }
                    else if(Grid[XYToIndex(jWidth - 1, iHeight)] != ModuleType)
                    {
                        ModuleRotation.Yaw = 180;
                    }

                    ModuleClass = TModule;
                }
                else if (WallsCount == 3) // Dead end
                {
                    if (Grid[XYToIndex(jWidth, iHeight - 1)] == ModuleType)
                    {
                        ModuleRotation.Yaw = 180;
                    }
                    else if (Grid[XYToIndex(jWidth, iHeight + 1)] == ModuleType)
                    {
                        ModuleRotation.Yaw = 0;
                    }
                    else if (Grid[XYToIndex(jWidth - 1, iHeight)] == ModuleType)
                    {
                        ModuleRotation.Yaw = 90;
                    }
                    else
                    {
                        ModuleRotation.Yaw = -90;
                    }
                    ModuleClass = DeadEndModule;
                }
                else if (WallsCount == 4) // Crossroad
                {
                    // not needed for now
                }

                if(ModuleClass != nullptr)
                {
                    FActorSpawnParameters SpawnParameters;
                    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                    const FTransform Transform(ModuleRotation, FVector{ MazeX + jWidth * ModuleSize, MazeY + iHeight * ModuleSize, 0 });

                    GetWorld()->SpawnActor(ModuleClass, &Transform, SpawnParameters);
                }
            }
        }
    }
}

void AUnrealProjectGameMode::ResetGrid() const
{
    // Fills the grid with walls.
    for (int i=0; i < Width * Height; ++i)
    {
        Grid[i] = WALL;
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
            if (Grid[XYToIndex(x2, y2)] == WALL)
            {
                // (x2,y2) has not been visited yet...knock down the
                // wall between my current position and that position
                Grid[XYToIndex(x2 - dx, y2 - dy)] = GROUND;
                // Recursively Visit (x2,y2)
                Visit(x2, y2);
            }
        }
    }

    for(int i = 1; i < Height-1; i+=2)
    {
        for(int j = 1; j < Width-1; j+=2)
        {
            if(NumberOfWalls(i, j, GROUND) == 3)
            {
                BreakDeadEndWall(j, i);
            }
        }
    }
}

int AUnrealProjectGameMode::NumberOfWalls(const int x, const int y, const EModuleType& ModuleType) const
{
    int WallsCount = 0;

    if(x - 1 < 0 || Grid[XYToIndex(x - 1, y)] != ModuleType)
    {
        WallsCount++;
    }

    if (x + 1 > Width || Grid[XYToIndex(x + 1, y)] != ModuleType)
    {
        WallsCount++;
    }

    if (y - 1 < 0 || Grid[XYToIndex(x, y - 1)] != ModuleType)
    {
        WallsCount++;
    }

    if (y + 1 > Height || Grid[XYToIndex(x, y + 1)] != ModuleType)
    {
        WallsCount++;
    }

    return WallsCount;
}

void AUnrealProjectGameMode::BreakDeadEndWall(const int x, const int y) const
{
    if (Grid[XYToIndex(x - 1, y)] == GROUND)
    {
        BreakWall(x + 1, y);
    }
    else if (Grid[XYToIndex(x + 1, y)] == GROUND)
    {
        BreakWall(x - 1, y);
    }
    else if (Grid[XYToIndex(x, y - 1)] == GROUND)
    {
        BreakWall(x, y + 1);
    }
    else if (Grid[XYToIndex(x, y + 1)] == GROUND)
    {
        BreakWall(x, y - 1);
    }
}

void AUnrealProjectGameMode::BreakWall(const int x, const int y) const
{
    if(x < 0 || y < 0 || x >= Width || y >= Height)
    {
        return;
    }

    Grid[XYToIndex(x, y)] = GROUND;
}

