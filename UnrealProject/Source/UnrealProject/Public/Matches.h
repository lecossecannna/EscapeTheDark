// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Matches.generated.h"

class UInteractiveObject;
class UBoxComponent;
UCLASS()
class UNREALPROJECT_API AMatches : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMatches();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
		UBoxComponent* Collider = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractiveObject")
		UInteractiveObject* InterOBJ = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
