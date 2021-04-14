// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleWall.generated.h"

UCLASS()
class UNREALPROJECT_API ASimpleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleWall();

protected:

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent = nullptr;
};
