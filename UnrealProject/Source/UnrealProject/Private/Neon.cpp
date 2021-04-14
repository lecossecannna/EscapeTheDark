// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealProject/Public/Neon.h"


#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ANeon::ANeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("ParticleSystem")));
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("PlayerLight"));
	if(Mesh)
	{
		SetRootComponent(Mesh);
	}
	if(Collision)
	{
		Collision->SetupAttachment(RootComponent);
	}
	if(Particle)
	{
		Particle->SetupAttachment(RootComponent);
		Particle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	if (Light)
	{
		Light->SetupAttachment(RootComponent);
		Light->SetVisibility(false);
	}

	//CreateSound
	Sounds = CreateDefaultSubobject<USceneComponent>(FName("Sounds"));
	SoundAnim = CreateDefaultSubobject<UAudioComponent>(FName(TEXT("MatchSound")));
	if (Sounds != nullptr)
	{
		Sounds->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		if (SoundAnim)
		{
			SoundAnim->SetupAttachment(Sounds);
			SoundAnim->bAutoActivate = false;
		}
	}
}

void ANeon::StartAnimation()
{
	bAnimation = true;
}

void ANeon::DesactiveLight()
{
	Light->SetVisibility(false);
	btest = false;
}

bool ANeon::IsVisible()
{

	return Light->IsVisible();
}

void ANeon::ActiveLight()
{
	Light->SetVisibility(true);
}

void ANeon::AnimationEnd()
{
	bAnimation = false;
	DesactiveLight();
}

// Called when the game starts or when spawned
void ANeon::BeginPlay()
{
	Super::BeginPlay();
	if(Particle)
	{
		Particle->DeactivateSystem();
	}
}

// Called every frame
void ANeon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bAnimation) 
	{

		 if(bCallStop == false)
		 {
		  RunAnimation();
		  GetWorldTimerManager().SetTimer(HitTimeHandle, this, &ANeon::AnimationEnd, AnimDuration);
		  bCallStop = true;
		 }

		
	}
}

void ANeon::RunAnimation()
{
  if(btest == false ) {
	  btest = true;
	  float timingToDesactive = FMath::RandRange(0.1f, MaxTimingToDesactive);
	  GetWorldTimerManager().SetTimer(HitTimeHandleEnd, this, &ANeon::DesactiveLight, timingToDesactive);
  }
  ActiveLight();
float timingToActive = FMath::RandRange(0.2f, MaxTimingToActive);
GetWorldTimerManager().SetTimer(HitTimeHandleStart, this, &ANeon::RunAnimation, timingToActive);
}

