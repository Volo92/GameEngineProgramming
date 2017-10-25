// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackGameState.h"
#include <Engine.h>

ATimeAttackGameState::ATimeAttackGameState()
{
	// In setup, set all time to zero.
	m_StartTimeLap = 0.0f;
	m_StartTimeRace = 0.0f; 
	m_EndTimeLap = 0.0f; 
	m_EndTimeRace = 0.0f;
	m_CurrentTime = 0.0f;

	PrimaryActorTick.bCanEverTick = true;
}

void ATimeAttackGameState::HandleBeginPlay()
{
	// Set the RaceStart to false and get the PlayerState from the dedicated array in the GameState.
	m_RaceStart = false;
	m_PlayerState = Cast<ATimeAttackPlayerState>(PlayerArray[0]);
	Super::HandleBeginPlay();
}

void ATimeAttackGameState::Tick(float DeltaSeconds)
{
	// If the race started, it updates the current time to display it in game HUD.
	if (m_RaceStart)
	{
		m_CurrentTime = GetWorld()->GetTimeSeconds() - m_StartTimeRace;
		m_PlayerState->SetActualRaceTime(m_CurrentTime);
		m_PlayerState->SetActualRaceTimeText(ATimeConversion::ReturnText(m_CurrentTime));
	}
	Super::Tick(DeltaSeconds);
}

float ATimeAttackGameState::CheckNewRecordLap(float BestLap)
{
	// Calculates the lap time, display it in debug form and check if the lap time is the best.
	m_EndTimeLap = GetWorld()->GetTimeSeconds();
	float lapTime = m_EndTimeLap - m_StartTimeLap;
	m_StartTimeLap = GetWorld()->GetTimeSeconds();
	FString LapTimeText = "New lap time: " + ATimeConversion::ReturnText(lapTime).ToString();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, LapTimeText);
	// Return the best lap time in all cases to check with the GameMode.
	if (lapTime < BestLap)
	{
		// New record lap, substitute the old record lap and draw it in the HUD.
		m_PlayerState->SetBestPlayerLap(lapTime);
		m_PlayerState->SetBestPlayerLapText(ATimeConversion::ReturnText(lapTime));
		return lapTime;
	}
	else
	{
		return BestLap;
	}
}

float ATimeAttackGameState::CheckNewRecordTime(float BestTime)
{
	// Calculates the race time and check if it is the best.
	m_EndTimeRace = GetWorld()->GetTimeSeconds();
	float RaceTime = m_EndTimeRace - m_StartTimeRace;
	if (RaceTime < BestTime)
	{
		// New race record, substitute the old record and draw it in the HUD.
		m_PlayerState->SetBestPlayerTime(RaceTime);
		m_PlayerState->SetBestPlayerTimeText(ATimeConversion::ReturnText(RaceTime));
		return RaceTime;
	}
	else
	{
		return BestTime;
	}
}

void ATimeAttackGameState::SetStartTimeRace(const float StartTimeRace)
{
	m_StartTimeRace = StartTimeRace;
}

float ATimeAttackGameState::GetStartTimeRace() const
{
	return m_StartTimeRace;
}

void ATimeAttackGameState::SetEndTimeRace(const float EndTimeRace)
{
	m_EndTimeRace = EndTimeRace;
}

float ATimeAttackGameState::GetEndTimeRace() const
{
	return m_EndTimeRace;
}

void ATimeAttackGameState::SetStartTimeLap(const float StartTimeLap)
{
	m_StartTimeLap = StartTimeLap;
}

float ATimeAttackGameState::GetStartTimeLap() const
{
	return m_StartTimeLap;
}

void ATimeAttackGameState::SetEndTimeLap(const float EndTimeLap)
{
	m_EndTimeLap = EndTimeLap;
}

float ATimeAttackGameState::GetEndTimeLap() const
{
	return m_EndTimeLap;
}

float ATimeAttackGameState::GetCurrentTime() const
{
	return m_CurrentTime;
}

void ATimeAttackGameState::SetRaceStart(const bool RaceStart)
{
	m_RaceStart = RaceStart;
}

bool ATimeAttackGameState::IsRaceStart() const
{
	return m_RaceStart;
}
