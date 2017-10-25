// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TimeAttackPlayerState.generated.h"

/**
 *  This class manages all the player's values
 */
UCLASS()
class TIMEATTACKVOLO_API ATimeAttackPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:

	// Values of the player
	UPROPERTY(BlueprintReadOnly, Category = "ValueVariables")
		int m_ActualLap;
	UPROPERTY(BlueprintReadOnly, Category = "ValueVariables")
		float m_ActualRaceTime;
	UPROPERTY(BlueprintReadOnly, Category = "ValueVariables")
		float m_BestPlayerLap;
	UPROPERTY(BlueprintReadOnly, Category = "ValueVariables")
		float m_BestPlayerTime;
	// Values of the race
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRace")
		bool b_RaceComplete;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRace")
		int m_MaxLaps;

	// Texts to draw in the HUD
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_ActualLapText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_ActualRaceTimeText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_BestPlayerLapText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_BestPlayerRaceTime;

public:

	ATimeAttackPlayerState();

	// Check if the race is complete and in the case it is not update the lap.
	void UpdateLap();

	// Set the RaceComplete value.
	UFUNCTION()
		bool RaceCompleteCheck();

	// Getters and Setters
	void SetActualLap(const int ActualLap);
	int GetActualLap() const;
	void SetActualRaceTime(const float ActualRaceTime);
	float GetActualRaceTime() const;
	void SetBestPlayerLap(const float BestPlayerLap);
	float GetBestPleyerLap() const;
	void SetBestPlayerTime(const float BestPlayerTime);
	float GetBestPlayerTime() const;
	void SetRaceComplete(const bool RaceComplete);
	bool IsRaceComplete() const;
	void SetMaxLaps(const int MaxLaps);
	int GetMaxLaps() const;
	void SetActualLapText(const FText ActualLapText);
	FText GetActualLapText() const;
	void SetActualRaceTimeText(const FText ActualRaceTimeText);
	FText GetActualRaceTimeText() const;
	void SetBestPlayerLapText(const FText BestPlayerLapText);
	FText GetBestPlayerLapText() const;
	void SetBestPlayerTimeText(const FText BestPlayerTimeText);
	FText GetBestPlayerTimeText() const;

	
};
