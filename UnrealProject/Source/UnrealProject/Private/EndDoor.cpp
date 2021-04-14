// Fill out your copyright notice in the Description page of Project Settings.


#include "EndDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndDoor::AEndDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

	RootComponent = MeshComponent;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

