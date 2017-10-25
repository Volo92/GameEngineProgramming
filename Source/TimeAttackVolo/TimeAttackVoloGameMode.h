// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Checkpoint.h"
#include "TimeAttackPlayerState.h"
#include "TimeAttackGameState.h"
#include "TimeAttackPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "TimeAttackSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TimeConversion.h"
#include "TimeAttackVoloGameMode.generated.h"

UCLASS(MinimalAPI)
class ATimeAttackVoloGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ATimeAttackVoloGameMode();
	// The method to setup all the game. Called before BeginPlay().
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// This two method are used to find and select the PlayerStart, for the spawn point.
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;
	// Call this method at the end of a timer.
	void EndTimer();

protected:
	
	// Race settings.
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		int m_MaxLaps;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_GoldTime;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_SilverTime;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_BronzeTime;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_DefaultBestLap;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_DefaultBestTime;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_BestLap;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		float m_BestTime;
	UPROPERTY(EditAnywhere, Category = "CustomSettings")
		FString m_SaveGameName;
	// Checkpoints settings.
	UPROPERTY(EditAnywhere, Category = "Checkpoints")
		TArray<ACheckpoint*> m_Checkpoints;
	UPROPERTY(EditAnywhere, Category = "Checkpoints")
		int m_TotalCheckpoints;
	UPROPERTY(EditAnywhere, Category = "Checkpoints")
		int m_lastCheckpoint;

	// Text to draw in the HUD.
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_MaxLapsText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_GoldTimeText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_SilverTimeText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_BronzeTimeText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_BestLapText;
	UPROPERTY(BlueprintReadOnly, Category = "TextVariable")
		FText m_BestTimeText;

	// Reference to other game's component.
	UPROPERTY(BlueprintReadOnly)
		ATimeAttackPlayerState* m_PlayerState;
	UPROPERTY(BlueprintReadOnly)
		APlayerStart* m_PlayerStart;
	UPROPERTY(BlueprintReadOnly)
		ATimeAttackPlayerController* m_PlayerController;

	// Set the checkpoints for the race.
	void StartSequence();	

public:

	// Initialize the texts for the HUD
	UFUNCTION()
		void InitText();
	// Call when the vehicle pass a checkpoint.
	UFUNCTION()
		void CheckpoitCleared(int NextCheckpoint);
	// Activate a checkpoint.
	UFUNCTION()
		void ActivateCheckpoint(ACheckpoint* NextCheckpoint);
	// Control the race flow and if the race is over restart the race from the beginning.
	UFUNCTION()
		void LapCheck(int Checkpoint);
	// Check if the save game exists.
	UFUNCTION()
		void SaveGameCheck();
	// Save the game.
	UFUNCTION()
		void SaveTheGame();
	// Load the game.
	UFUNCTION()
		void LoadTheGame();
	// Reset the record times values in the default values.
	UFUNCTION()
		void ResetRecord();

	// Getters and Setters
	void SetMaxLaps(const int MaxLaps);
	int GetMaxLaps() const;
	void SetGoldTime(const float GoldTime);
	float GetGoldTime() const;
	void SetSilverTime(const float SilverTime);
	float GetSilverTime() const;
	void SetBronzeTime(const float BronzeTime);
	float GetBronzeTime() const;
	void SetDefaultBestLap(const float DefaultBestLap);
	float GetDefaultBestLap() const;
	void SetDefaultBestTime(const float DefaultBestTime);
	float GetDefaultBestTime() const;
	void SetBestLap(const float BestLap);
	float GetBestLap() const;
	void SetBestTime(const float BestTime);
	float GetBestTime() const;
	void SetSaveGameName(const FString SaveGameName);
	FString GetSaveGameName() const;
	void SetCheckpoints(const TArray<ACheckpoint*> Checkpoints);
	TArray<ACheckpoint*> GetCheckpoints() const;
	void SetTotalCheckpoints(const int TotalCheckpoints);
	int GetTotalCheckpoints() const;
	void SetMaxLapsText(const FText MaxLapsText);
	FText GetMaxLapsText() const;
	void SetGoldTimeText(const FText GoldTimeText);
	FText GetGoldTimeText() const;
	void SetSilverTimeText(const FText SilverTimeText);
	FText GetSilverTimeText() const;
	void SetBronzeTimeText(const FText BronzeTimeText);
	FText GetBronzeTimeText() const;
	void SetBestLapText(const FText BestLapText);
	FText GetBestLapText() const;
	void SetBestTimeText(const FText BestTimeText);
	FText GetBestTimeText() const;
	void SetPlayerState(ATimeAttackPlayerState* const PlayerState);
	ATimeAttackPlayerState* GetPlayerState() const;

};
