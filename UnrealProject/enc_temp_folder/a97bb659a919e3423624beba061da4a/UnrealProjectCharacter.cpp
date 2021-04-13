// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProjectCharacter.h"

#include "InteractiveObject.h"
#include "UnrealProjectProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUnrealProjectCharacter

AUnrealProjectCharacter::AUnrealProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//CreateLight
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PlayerLight"));
	if(Light)
	{
		Light->SetupAttachment(FirstPersonCameraComponent);
		Light->SetIntensity(0);
	}

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveBox"));
	if(InteractionBox)
	{
		InteractionBox->SetupAttachment(RootComponent);
		InteractionBox->SetCollisionProfileName(TEXT("Trigger"));
	}
	
	//CreateSound
	Sounds = CreateDefaultSubobject<USceneComponent>(FName("Sounds"));
	SoundMatch = CreateDefaultSubobject<UAudioComponent>(FName(TEXT("MatchSound")));
	if (Sounds != nullptr)
	{
		Sounds->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		if(SoundMatch)
		{
			SoundMatch->SetupAttachment(Sounds);
			SoundMatch->bAutoActivate = false;
		}
	}
	
}

void AUnrealProjectCharacter::Tick(float DeltaSeconds)
{
	if(bLightIsActive)
	{
		AnimLight(DeltaSeconds);
	}
}

void AUnrealProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnrealProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind light of player
	PlayerInputComponent->BindAction("ActiveLight", IE_Pressed, this, &AUnrealProjectCharacter::ActiveLight);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AUnrealProjectCharacter::ActiveInteractionBox);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealProjectCharacter::LookUpAtRate);
}

void AUnrealProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUnrealProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUnrealProjectCharacter::ActiveLight()
{
	if(bLightIsActive == false)
	{
		if(!SoundMatch->IsPlaying())
		{
			SoundMatch->Activate(true);
		}
		bLightIsActive = true;
		GetWorldTimerManager().SetTimer(HitTimeHandle, this, &AUnrealProjectCharacter::DesactiveLight, LightDuration);
	}
}

void AUnrealProjectCharacter::DesactiveLight()
{
	AlphaLerpLight = 0.0f;
	Light->SetIntensity(0.f);
	bLightIsActive = false;
}

void AUnrealProjectCharacter::AnimLight(float DeltaSeconds)
{
	AlphaLerpLight += SpeedTransition * DeltaSeconds;
	FMath::Clamp(AlphaLerpLight, 0.f, 1.f); 
	float intensity = FMath::Lerp(StartLightBrightess, LightBrightess, AlphaLerpLight);
	Light->SetIntensity(intensity);
}

void AUnrealProjectCharacter::ActiveInteractionBox()
{
	TArray<AActor*>actors;
	InteractionBox->GetOverlappingActors(actors);
        for(auto*  actor : actors) 
	{
		UInteractiveObject* component = actor->FindComponentByClass<UInteractiveObject>();
		  if(component) {
			  component->bIsSelected = true;
		  }
        }
	//FindComponentByClass<UInteractiveObject>(actors);
	//GetWorldTimerManager().SetTimer(HitTimeHandleInteraction, this, &AUnrealProjectCharacter::DesactiveInteractionBox, 1.f);

}

void AUnrealProjectCharacter::DesactiveInteractionBox()
{
	InteractionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

void AUnrealProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
