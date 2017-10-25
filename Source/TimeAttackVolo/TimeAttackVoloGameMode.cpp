// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TimeAttackVoloGameMode.h"
#include "TimeAttackVoloPawn.h"
#include "TimeAttackVoloHud.h"

#include "Engine/World.h"
#include <Engine.h>


ATimeAttackVoloGameMode::ATimeAttackVoloGameMode()
{
	// Define the class for the game's components
	DefaultPawnClass = ATimeAttackVoloPawn::StaticClass();
	PlayerStateClass = ATimeAttackPlayerState::StaticClass();
	GameStateClass = ATimeAttackGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void ATimeAttackVoloGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	// Set the default value for the race.
	m_MaxLaps = 3;
	m_GoldTime = 60.0f;
	m_SilverTime = 90.0f;
	m_BronzeTime = 120.0f;
	m_DefaultBestLap = 20.0f;
	m_DefaultBestTime = 60.0f;
	m_SaveGameName = "Volo_SaveGame";
	m_lastCheckpoint = 99;

	// Create all the checkpoints for the race.
	m_TotalCheckpoints = 10;
	ACheckpoint* Checkpoint_0 = (ACheckpoint*) GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_0->SetActorLocation(FVector(1090.0f, 2610.0f, 200.0f));
	m_Checkpoints.Add(Checkpoint_0);

	ACheckpoint* Checkpoint_1 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_1->SetActorLocation(FVector(2340.0f, 1840.0f, 200.0f));
	Checkpoint_1->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_1);

	ACheckpoint* Checkpoint_2 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_2->SetActorLocation(FVector(1590.0f, 780.0f, 200.0f));
	Checkpoint_2->SetActorRotation(FRotator(0.0f, -180.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_2);

	ACheckpoint* Checkpoint_3 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_3->SetActorLocation(FVector(470.0f, 250.0f, 200.0f));
	Checkpoint_3->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_3);

	ACheckpoint* Checkpoint_4 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_4->SetActorLocation(FVector(1310.0f, -450.0f, 200.0f));
	m_Checkpoints.Add(Checkpoint_4);

	ACheckpoint* Checkpoint_5 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_5->SetActorLocation(FVector(2570.0f, -1730.0f, 200.0f));
	Checkpoint_5->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_5);

	ACheckpoint* Checkpoint_6 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_6->SetActorLocation(FVector(510.0f, -2810.0f, 200.0f));
	Checkpoint_6->SetActorRotation(FRotator(0.0f, -180.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_6);

	ACheckpoint* Checkpoint_7 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_7->SetActorLocation(FVector(-1610.0f, -940.0f, 200.0f));
	Checkpoint_7->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_7);

	ACheckpoint* Checkpoint_8 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_8->SetActorLocation(FVector(-1910.0f, 1170.0f, 200.0f));
	Checkpoint_8->SetActorRotation(FRotator(0.0f, 70.0f, 0.0f));
	m_Checkpoints.Add(Checkpoint_8);

	ACheckpoint* Checkpoint_9 = (ACheckpoint*)GetWorld()->SpawnActor(ACheckpoint::StaticClass());
	Checkpoint_9->SetActorLocation(FVector(350.0f, 2640.0f, 200.0f));
	m_Checkpoints.Add(Checkpoint_9);

	StartSequence();
}

void ATimeAttackVoloGameMode::BeginPlay()
{
	// Take the player state, check if exists a save game and initialize the text for the HUD.
	m_PlayerState = Cast<ATimeAttackPlayerState>(GetGameState<ATimeAttackGameState>()->PlayerArray[0]);	
	SaveGameCheck();
	InitText();
}

void ATimeAttackVoloGameMode::Tick(float DeltaSeconds)
{
	// Used for reset the record times, only before the race's start.
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::R) && !GetGameState<ATimeAttackGameState>()->IsRaceStart())
	{
		ResetRecord();
	}
	Super::Tick(DeltaSeconds);
}

AActor * ATimeAttackVoloGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	// Select the PlayerStart and return it.
	m_PlayerStart = Cast<APlayerStart>(Super::ChoosePlayerStart_Implementation(Player));
	return m_PlayerStart;
}

AActor * ATimeAttackVoloGameMode::FindPlayerStart_Implementation(AController * Player, const FString & IncomingName)
{
	// If there is this value the race is not started.
	if (m_lastCheckpoint == 99)
	{
		return Super::FindPlayerStart_Implementation(Player, IncomingName);
	}
	else
	{
		// Set the respawn point at last checkpoint.
		AActor* RestartSpawn = Cast<AActor>(m_Checkpoints[m_lastCheckpoint]);
		return RestartSpawn;
	}	
}

void ATimeAttackVoloGameMode::EndTimer()
{
	// At the end of the timer restart the level.
	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void ATimeAttackVoloGameMode::InitText()
{
	// Initialize all the test for the HUD, converting the float in a adequate string.
	m_PlayerState->SetActualLapText(FText::FromString(FString::FromInt(m_PlayerState->GetActualLap())));
	m_MaxLapsText = FText::FromString(FString::FromInt(m_MaxLaps));
	m_GoldTimeText = ATimeConversion::ReturnText(m_GoldTime);
	m_SilverTimeText = ATimeConversion::ReturnText(m_SilverTime);
	m_BronzeTimeText = ATimeConversion::ReturnText(m_BronzeTime);
	m_BestLapText = ATimeConversion::ReturnText(m_BestLap);
	m_BestTimeText = ATimeConversion::ReturnText(m_BestTime);
}

void ATimeAttackVoloGameMode::CheckpoitCleared(int NextCheckpoint)
{
	// Called from the checkpoint.
	LapCheck(NextCheckpoint);
}

void ATimeAttackVoloGameMode::ActivateCheckpoint(ACheckpoint * NextCheckpoint)
{
	// Make the checkpoint visible.
	UBoxComponent* MyBox = NextCheckpoint->FindComponentByClass<UBoxComponent>();
	MyBox->bGenerateOverlapEvents = true;

	UParticleSystemComponent* MyParticle = NextCheckpoint->FindComponentByClass<UParticleSystemComponent>();
	MyParticle->SetHiddenInGame(false);

}

void ATimeAttackVoloGameMode::LapCheck(int Checkpoint)
{
	// Check if the checkpoint passed is the last.
	if (Checkpoint == m_TotalCheckpoints)
	{
		// Check if this lap is the best.
		m_BestLap = GetGameState<ATimeAttackGameState>()->CheckNewRecordLap(m_BestLap);
		if (!m_PlayerState->RaceCompleteCheck())
		{
			// If the race is not complete activate the first checkpoint and update the lap of the player.
			ActivateCheckpoint(m_Checkpoints[0]);
			m_PlayerState->UpdateLap();			
		}
		else
		{
			// If the race is complete check if the race time is the best and reset the race after the timer.
			m_BestTime = GetGameState<ATimeAttackGameState>()->CheckNewRecordTime(m_BestTime);
			FTimerHandle RestartLevel;
			GetWorld()->GetTimerManager().SetTimer(RestartLevel, this, &ATimeAttackVoloGameMode::EndTimer, 1.0f, false);			
		}
	}
	else
	{
		// The lap is not complete and activate the next checkpoint.
		ActivateCheckpoint(m_Checkpoints[Checkpoint]);
	}
	// Update the last checkpoint passed.
	m_lastCheckpoint = Checkpoint - 1;
	// Refresh the texts for the HUD.
	InitText();
	// Save the game with the new records.
	SaveTheGame();
}

void ATimeAttackVoloGameMode::SaveGameCheck()
{
	// Check if there is a save game.
	UTimeAttackSaveGame* LoadGameInstance = Cast<UTimeAttackSaveGame>(UGameplayStatics::CreateSaveGameObject(UTimeAttackSaveGame::StaticClass()));
	LoadGameInstance = Cast<UTimeAttackSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->m_SaveSlotGame, LoadGameInstance->m_UserIndex));
	if (LoadGameInstance == nullptr)
	{
		// if not it create a new one.
		m_BestLap = m_DefaultBestLap;
		m_BestTime = m_DefaultBestTime;
		SaveTheGame();
	}
	else
	{
		LoadTheGame();
	}
}

void ATimeAttackVoloGameMode::SaveTheGame()
{
	// Save the new record in the save game.
	UTimeAttackSaveGame* SaveGameInstance = Cast<UTimeAttackSaveGame>(UGameplayStatics::CreateSaveGameObject(UTimeAttackSaveGame::StaticClass()));
	SaveGameInstance->m_SavedBestLap = m_BestLap;
	SaveGameInstance->m_SavedBestTime = m_BestTime;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->m_SaveSlotGame, SaveGameInstance->m_UserIndex);
}

void ATimeAttackVoloGameMode::LoadTheGame()
{
	// Load the record from the save game.
	UTimeAttackSaveGame* LoadGameInstance = Cast<UTimeAttackSaveGame>(UGameplayStatics::CreateSaveGameObject(UTimeAttackSaveGame::StaticClass()));
	LoadGameInstance = Cast<UTimeAttackSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->m_SaveSlotGame, LoadGameInstance->m_UserIndex));
	m_BestLap = LoadGameInstance->m_SavedBestLap;
	m_BestTime = LoadGameInstance->m_SavedBestTime;
}

void ATimeAttackVoloGameMode::ResetRecord()
{
	// Reset the record times to the default values and save the game.
	m_BestTime = m_DefaultBestTime;
	m_BestLap = m_DefaultBestLap;
	m_BestLapText = ATimeConversion::ReturnText(m_BestLap);
	m_BestTimeText = ATimeConversion::ReturnText(m_BestTime);
	SaveTheGame();
}

void ATimeAttackVoloGameMode::StartSequence()
{
	// Initialize all checkpoints and activate the first one for the race.
	for (int i = 0; i < m_TotalCheckpoints; i++)
	{
		m_Checkpoints[i]->SetCheckpointNumber(i + 1);
		m_Checkpoints[i]->OnCheckpointCleared.AddDynamic(this, &ATimeAttackVoloGameMode::CheckpoitCleared);
	}
	ActivateCheckpoint(m_Checkpoints[0]);

}

void ATimeAttackVoloGameMode::SetMaxLaps(const int MaxLaps)
{
	m_MaxLaps = MaxLaps;
}

int ATimeAttackVoloGameMode::GetMaxLaps() const
{
	return m_MaxLaps;
}

void ATimeAttackVoloGameMode::SetGoldTime(const float GoldTime)
{
	m_GoldTime = GoldTime;
}

float ATimeAttackVoloGameMode::GetGoldTime() const
{
	return m_GoldTime;
}

void ATimeAttackVoloGameMode::SetSilverTime(const float SilverTime)
{
	m_SilverTime = SilverTime;
}

float ATimeAttackVoloGameMode::GetSilverTime() const
{
	return m_SilverTime;
}

void ATimeAttackVoloGameMode::SetBronzeTime(const float BronzeTime)
{
	m_BronzeTime = BronzeTime;
}

float ATimeAttackVoloGameMode::GetBronzeTime() const
{
	return m_BronzeTime;
}

void ATimeAttackVoloGameMode::SetDefaultBestLap(const float DefaultBestLap)
{
	m_DefaultBestLap = DefaultBestLap;
}

float ATimeAttackVoloGameMode::GetDefaultBestLap() const
{
	return m_DefaultBestLap;
}

void ATimeAttackVoloGameMode::SetDefaultBestTime(const float DefaultBestTime)
{
	m_DefaultBestTime = DefaultBestTime;
}

float ATimeAttackVoloGameMode::GetDefaultBestTime() const
{
	return m_DefaultBestTime;
}

void ATimeAttackVoloGameMode::SetBestLap(const float BestLap)
{
	m_BestLap = BestLap;
}

float ATimeAttackVoloGameMode::GetBestLap() const
{
	return m_BestLap;
}

void ATimeAttackVoloGameMode::SetBestTime(const float BestTime)
{
	m_BestTime = BestTime;
}

float ATimeAttackVoloGameMode::GetBestTime() const
{
	return m_BestTime;
}

void ATimeAttackVoloGameMode::SetSaveGameName(const FString SaveGameName)
{
	m_SaveGameName = SaveGameName;
}

FString ATimeAttackVoloGameMode::GetSaveGameName() const
{
	return m_SaveGameName;
}

void ATimeAttackVoloGameMode::SetCheckpoints(const TArray<ACheckpoint*> Checkpoints)
{
	m_Checkpoints = Checkpoints;
}

TArray<ACheckpoint*> ATimeAttackVoloGameMode::GetCheckpoints() const
{
	return m_Checkpoints;
}

void ATimeAttackVoloGameMode::SetTotalCheckpoints(const int TotalCheckpoints)
{
	m_TotalCheckpoints = TotalCheckpoints;
}

int ATimeAttackVoloGameMode::GetTotalCheckpoints() const
{
	return m_TotalCheckpoints;
}

void ATimeAttackVoloGameMode::SetMaxLapsText(const FText MaxLapsText)
{
	m_MaxLapsText = MaxLapsText;
}

FText ATimeAttackVoloGameMode::GetMaxLapsText() const
{
	return m_MaxLapsText;
}

void ATimeAttackVoloGameMode::SetGoldTimeText(const FText GoldTimeText)
{
	m_GoldTimeText = GoldTimeText;
}

FText ATimeAttackVoloGameMode::GetGoldTimeText() const
{
	return m_GoldTimeText;
}

void ATimeAttackVoloGameMode::SetSilverTimeText(const FText SilverTimeText)
{
	m_SilverTimeText = SilverTimeText;
}

FText ATimeAttackVoloGameMode::GetSilverTimeText() const
{
	return m_SilverTimeText;
}

void ATimeAttackVoloGameMode::SetBronzeTimeText(const FText BronzeTimeText)
{
	m_BronzeTimeText = BronzeTimeText;
}

FText ATimeAttackVoloGameMode::GetBronzeTimeText() const
{
	return m_BronzeTimeText;
}

void ATimeAttackVoloGameMode::SetBestLapText(const FText BestLapText)
{
	m_BestLapText = BestLapText;
}

FText ATimeAttackVoloGameMode::GetBestLapText() const
{
	return m_BestLapText;
}

void ATimeAttackVoloGameMode::SetBestTimeText(const FText BestTimeText)
{
	m_BestTimeText = BestTimeText;
}

FText ATimeAttackVoloGameMode::GetBestTimeText() const
{
	return m_BestTimeText;
}

void ATimeAttackVoloGameMode::SetPlayerState( ATimeAttackPlayerState* const PlayerState)
{
	m_PlayerState = PlayerState;
}

ATimeAttackPlayerState * ATimeAttackVoloGameMode::GetPlayerState() const
{
	return m_PlayerState;
}

