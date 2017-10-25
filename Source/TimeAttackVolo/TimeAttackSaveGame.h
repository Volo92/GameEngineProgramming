// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TimeAttackSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TIMEATTACKVOLO_API UTimeAttackSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	// Variables to save in the save game.
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		float m_SavedBestLap;
	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		float m_SavedBestTime;

	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		FString m_SaveSlotGame;

	UPROPERTY(VisibleAnywhere, Category = SaveGame)
		int32 m_UserIndex;
	
	UTimeAttackSaveGame();
	
};
