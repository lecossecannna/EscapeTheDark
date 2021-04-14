// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightButton.generated.h"

class UInteractiveObject;
class UBoxComponent;
class ANeon;
UCLASS()
class UNREALPROJECT_API ALightButton : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider")
		UBoxComponent* Collision = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractiveObject")
		UInteractiveObject* InterOBJ = nullptr;
public:	
	// Sets default values for this actor's properties
	ALightButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Sounds
	UPROPERTY(VisibleAnywhere, Category = "Sound")
		USceneComponent* Sounds = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
		UAudioComponent* SoundActiveButton = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActiveLight();
	void AddNeon(ANeon* TheNeon);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "MyNeon")
	TArray<ANeon*> Neon;
};
