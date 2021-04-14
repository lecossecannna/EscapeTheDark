// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class USphereComponent;
UCLASS()
class UNREALPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	AEnemyCharacter();

	/** Pawn mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* MyMesh = nullptr;
private:
  UFUNCTION()
	  virtual void BeginOverlapDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dettect")
		USphereComponent* RangeDetectionLight = nullptr;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Sounds = nullptr;

	UPROPERTY(VisibleAnywhere)
		UAudioComponent* SoundDefault = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
