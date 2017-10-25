// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include <ConstructorHelpers.h>


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set checkpoint's components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Trigger->SetWorldScale3D(FVector(1.0f, 8.0f, 8.0f));
	Trigger->SetHiddenInGame(true);
	Trigger->SetCollisionProfileName("OverlapOnlyPawn");
	Trigger->bGenerateOverlapEvents = false;
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnEndOverlap);

	ParticleSys = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSys->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ConstructorHelpers::FObjectFinder<UParticleSystem> MyParticle(TEXT("ParticleSystem'/Game/Particle/P_SparksCheckpoint.P_SparksCheckpoint'"));
	ParticleSys->SetTemplate(MyParticle.Object);
	ParticleSys->SetHiddenInGame(true);

}

void ACheckpoint::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	// Get the vehicle velocity and checkpoint rotation
	FVector VehicleVelocity = OtherActor->GetVelocity();
	FVector ArrowRotation = Arrow->GetComponentRotation().Vector();
	// Check the vehicle direction with the checkpoint rotation
	if (FVector::DotProduct(VehicleVelocity, ArrowRotation) > 0)
	{
		// The vehicle passes the checkpoint, disables it and activates the next
		Trigger->SetHiddenInGame(true);
		ParticleSys->SetHiddenInGame(true);
		Trigger->bGenerateOverlapEvents = false;
		OnCheckpointCleared.Broadcast(GetCheckpointNumber());
	}
}

