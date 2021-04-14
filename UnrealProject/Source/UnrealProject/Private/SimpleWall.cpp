// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleWall.h"

// Sets default values
ASimpleWall::ASimpleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

	RootComponent = MeshComponent;

}

