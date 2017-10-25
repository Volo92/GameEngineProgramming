// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeConversion.generated.h"

UCLASS()
class TIMEATTACKVOLO_API ATimeConversion : public AActor
{
	GENERATED_BODY()
	
public:	

	// Static function to convert float value in an appropriate string.
	static FText ReturnText(float val);
		
};
