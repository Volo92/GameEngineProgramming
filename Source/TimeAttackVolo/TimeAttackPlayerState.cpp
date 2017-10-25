// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackPlayerState.h"

ATimeAttackPlayerState::ATimeAttackPlayerState()
{
	// Setup the first lap and the max lap.
	m_ActualLap = 1;
	m_MaxLaps = 3;
}

void ATimeAttackPlayerState::UpdateLap()
{
	if (!b_RaceComplete)
	{
		// If the race is not complete increment the actual lap and draw it in the HUD.
		m_ActualLap++;
		m_ActualLapText = FText::FromString(FString::FromInt(m_ActualLap));
	}
}

bool ATimeAttackPlayerState::RaceCompleteCheck()
{
	// Check if the race is complete and set the boolean return value.
	if (m_ActualLap >= m_MaxLaps)
	{
		b_RaceComplete = true;
	}
	else
	{
		b_RaceComplete = false;
	}
	return b_RaceComplete;
}

void ATimeAttackPlayerState::SetActualLap(const int ActualLap)
{
	m_ActualLap = ActualLap;
}

int ATimeAttackPlayerState::GetActualLap() const
{
	return m_ActualLap;
}

void ATimeAttackPlayerState::SetActualRaceTime(const float ActualRaceTime)
{
	m_ActualRaceTime = ActualRaceTime;
}

float ATimeAttackPlayerState::GetActualRaceTime() const
{
	return m_ActualRaceTime;
}

void ATimeAttackPlayerState::SetBestPlayerLap(const float BestPlayerLap)
{
	m_BestPlayerLap = BestPlayerLap;
}

float ATimeAttackPlayerState::GetBestPleyerLap() const
{
	return m_BestPlayerLap;
}

void ATimeAttackPlayerState::SetBestPlayerTime(const float BestPlayerTime)
{
	m_BestPlayerTime = BestPlayerTime;
}

float ATimeAttackPlayerState::GetBestPlayerTime() const
{
	return m_BestPlayerTime;
}

void ATimeAttackPlayerState::SetRaceComplete(const bool RaceComplete)
{
	b_RaceComplete = RaceComplete;
}

bool ATimeAttackPlayerState::IsRaceComplete() const
{
	return b_RaceComplete;
}

void ATimeAttackPlayerState::SetMaxLaps(const int MaxLaps)
{
	m_MaxLaps = MaxLaps;
}

int ATimeAttackPlayerState::GetMaxLaps() const
{
	return m_MaxLaps;
}

void ATimeAttackPlayerState::SetActualLapText(const FText ActualLapText)
{
	m_ActualLapText = ActualLapText;
}

FText ATimeAttackPlayerState::GetActualLapText() const
{
	return m_ActualLapText;
}

void ATimeAttackPlayerState::SetActualRaceTimeText(const FText ActualRaceTimeText)
{
	m_ActualRaceTimeText = ActualRaceTimeText;
}

FText ATimeAttackPlayerState::GetActualRaceTimeText() const
{
	return m_ActualRaceTimeText;
}

void ATimeAttackPlayerState::SetBestPlayerLapText(const FText BestPlayerLapText)
{
	m_BestPlayerLapText = BestPlayerLapText;
}

FText ATimeAttackPlayerState::GetBestPlayerLapText() const
{
	return m_BestPlayerLapText;
}

void ATimeAttackPlayerState::SetBestPlayerTimeText(const FText BestPlayerTimeText)
{
	m_BestPlayerRaceTime = BestPlayerTimeText;
}

FText ATimeAttackPlayerState::GetBestPlayerTimeText() const
{
	return m_BestPlayerRaceTime;
}
