// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Checkpoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckpointCleared, int, d_NextCheckpoint);

UCLASS()
class TIMEATTACKVOLO_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Object components
	USceneComponent* Root;
	UArrowComponent* Arrow;
	UBoxComponent* Trigger;
	UParticleSystemComponent* ParticleSys;

	// Variable to index the checkpoint
	UPROPERTY(Category = "CheckpointVariable", EditAnywhere)
	int m_CheckpointNumber;

	// Function for the trigger
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	// Delegate function to call when you pass the checkpoint
	UPROPERTY(BlueprintAssignable)
		FCheckpointCleared OnCheckpointCleared;

	// Setter & Getter for the variables
	FORCEINLINE int GetCheckpointNumber() const { return m_CheckpointNumber; };
	FORCEINLINE void SetCheckpointNumber(const int CheckpointNumber) { m_CheckpointNumber = CheckpointNumber; };
	
};
