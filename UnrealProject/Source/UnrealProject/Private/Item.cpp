// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Components/BoxComponent.h"
#include "UnrealProject/Public/InteractiveObject.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	if (Collision)
	{
		SetRootComponent(Collision);
	}
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if(Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
	}
	
	InterOBJ = CreateDefaultSubobject<UInteractiveObject>(TEXT("InteractiveOBJ"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InterOBJ->bIsSelected)
	{
		
	}
}

