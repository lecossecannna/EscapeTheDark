// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDoor.generated.h"

class UBoxComponent;
UCLASS()
class UNREALPROJECT_API AEndDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndDoor();

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision = nullptr;

};
