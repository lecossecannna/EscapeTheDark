// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRoom.h"
#include "UnrealProjectGameMode.h"

std::random_device Rd;
std::mt19937 Gen(Rd());

UMazeRoom::UMazeRoom()
{

}

UMazeRoom::~UMazeRoom()
{
    delete[] RoomWalls;
}

void UMazeRoom::SetWalls(AUnrealProjectGameMode* Mode, int* Walls, const int Height, const int Width)
{
    delete[] RoomWalls;

    RoomWalls = new int[Height * Width];

    for (int i = 0; i < Height * Width; i++)
    {
        RoomWalls[i] = Walls[i];
    }

    RoomHeight = Height;
    RoomWidth = Width;

    GameMode = Mode;
}

bool UMazeRoom::GenerateRoom()
{
    const std::uniform_int_distribution<int> DisHeight(0, GameMode->Height - 1);
    const std::uniform_int_distribution<int> DisWidth(0, GameMode->Width - 1);

    for(int i = 0; i < 500; i++)
    {
        const int x = DisWidth(Gen);
        const int y = DisHeight(Gen);

        for(int j = x; j < x + RoomWidth; j++)
        {
            for(int k = y; k < y + RoomHeight; k++)
            {
                
            }
        }
    }

    return false;
}
