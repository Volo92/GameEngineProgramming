// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TimeAttackVoloHud.generated.h"

UCLASS(config = Game)
class ATimeAttackVoloHud : public AHUD
{
	GENERATED_BODY()

public:
	ATimeAttackVoloHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
