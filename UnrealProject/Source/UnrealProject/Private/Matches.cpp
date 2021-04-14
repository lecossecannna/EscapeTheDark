// Fill out your copyright notice in the Description page of Project Settings.


#include "Matches.h"
#include "UnrealProject/Public/InteractiveObject.h"
#include "Components/BoxComponent.h"

// Sets default values
AMatches::AMatches()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	if (Collider)
	{
		SetRootComponent(Collider);
	}
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
	}

	InterOBJ = CreateDefaultSubobject<UInteractiveObject>(TEXT("InteractiveOBJ"));

}

// Called when the game starts or when spawned
void AMatches::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMatches::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

