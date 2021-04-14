// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UBoxComponent;
class UInteractiveObject;
UCLASS()
class UNREALPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
		UBoxComponent* Collision = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractiveObject")
		UInteractiveObject* InterOBJ = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
		int Index = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
