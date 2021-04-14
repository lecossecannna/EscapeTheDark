// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AUnrealProjectCharacter;
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

  AUnrealProjectCharacter* Player;
  bool bCheckItens = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dettect")
		USphereComponent* RangeDetectionLight = nullptr;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Sounds = nullptr;

	UPROPERTY(VisibleAnywhere)
		UAudioComponent* SoundDefault = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DontTuch)
		bool bContactPlayer = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float StartSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed1 = 350;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed2 = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed3 = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed4 = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed5 = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpeedPlayer)
		float Speed6 = 1200;
};
