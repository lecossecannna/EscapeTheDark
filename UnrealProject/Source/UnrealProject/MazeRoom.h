// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeRoom.generated.h"

UCLASS()
class UNREALPROJECT_API AMazeRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
