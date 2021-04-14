// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealProject/Public/EnemyCharacter.h"



#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "UnrealProject/Public/Neon.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	 // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	if (MyMesh)
	{
		MyMesh->SetupAttachment(RootComponent);
	}
	
	RangeDetectionLight = CreateDefaultSubobject<USphereComponent>(TEXT("RangeDetectionLight"));
	if (RangeDetectionLight)
	{
		RangeDetectionLight->SetupAttachment(RootComponent);
		RangeDetectionLight->SetCollisionProfileName(TEXT("Trigger"));
		RangeDetectionLight->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::BeginOverlapDetection);
	}

	//CreateSound
	Sounds = CreateDefaultSubobject<USceneComponent>(FName("Sounds"));
	SoundDefault = CreateDefaultSubobject<UAudioComponent>(FName(TEXT("MatchSound")));
	if (Sounds != nullptr)
	{
		Sounds->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		if (SoundDefault)
		{
			SoundDefault->SetupAttachment(Sounds);
			SoundDefault->bAutoActivate = false;
		}
	}
}

void AEnemyCharacter::BeginOverlapDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
      if(OtherActor == this) 
      {
           return;
      }
      ANeon* neon = Cast<ANeon>(OtherActor);
      if (neon)
      {
	      neon->StartAnimation();
      }
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
  Super::BeginPlay();
 
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
