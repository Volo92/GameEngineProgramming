// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TimeAttackPlayerState.h"
#include "TimeConversion.h"
#include "TimeAttackGameState.generated.h"

/*
** In the GameState class is handled the playing time, we use it to check the record times.
** Some method is used from blueprint for the HUD's management.
** I set both the best times in PlayerState and GameMode for a future application where there is more
** then one player.
*/
UCLASS()
class TIMEATTACKVOLO_API ATimeAttackGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ATimeAttackGameState();
	// The HandleBeginPlay() is different from the normal BeginPlay() because is called first of all. 
	// It is present only in this class.
	virtual void HandleBeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:

	// Variable for the time management.
	UPROPERTY(BlueprintReadOnly, Category = "Timers")
		float m_StartTimeRace;
	UPROPERTY(BlueprintReadOnly, Category = "Timers")
		float m_EndTimeRace;
	UPROPERTY(BlueprintReadOnly, Category = "Timers")
		float m_StartTimeLap;
	UPROPERTY(BlueprintReadOnly, Category = "Timers")
		float m_EndTimeLap;
	UPROPERTY(BlueprintReadOnly, Category = "Timers")
		float m_CurrentTime;

	// Reference to the PlayerState.
	UPROPERTY(BlueprintReadOnly, Category = "PlayerState")
		ATimeAttackPlayerState* m_PlayerState;

	// Boolean for the start of the race.
	UPROPERTY(BlueprintReadOnly, Category = "Start")
		bool m_RaceStart;

public:

	// Method to check the record times.
	UFUNCTION()
		float CheckNewRecordLap(float BestLap);
	UFUNCTION()
		float CheckNewRecordTime(float BestTime);

	// Getter and Setter. Someone is used in the HUD's blueprint.
	UFUNCTION(BlueprintCallable)
		void SetStartTimeRace(const float StartTimeRace);
	float GetStartTimeRace() const;
	void SetEndTimeRace(const float EndTimeRace);
	float GetEndTimeRace() const;
	UFUNCTION(BlueprintCallable)
		void SetStartTimeLap(const float StartTimeLap);
	float GetStartTimeLap() const;
	void SetEndTimeLap(const float EndTimeLap);
	float GetEndTimeLap() const;
	UFUNCTION(BlueprintCallable)
		float GetCurrentTime() const;
	UFUNCTION(BlueprintCallable)
		void SetRaceStart(const bool RaceStart);
	bool IsRaceStart() const;
	
};
