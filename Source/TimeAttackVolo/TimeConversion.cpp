// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeConversion.h"

FText ATimeConversion::ReturnText(float val)
{
	// Minutes
	FString MinutesText;
	int Minutes = val / 60;
	if (Minutes > 9)
	{
		MinutesText = FString::FromInt(Minutes);
	}
	else
	{
		MinutesText = "0" + FString::FromInt(Minutes);
	}

	// Seconds
	FString SecondsText;
	int Seconds = val;
	Seconds = Seconds % 60;
	if (Seconds > 9)
	{
		SecondsText = FString::FromInt(Seconds);
	}
	else
	{
		SecondsText = "0" + FString::FromInt(Seconds);
	}

	// Milliseconds
	FString MSecondsText;
	int MSeconds = val;
	MSeconds = (val - MSeconds) * 100;
	if (MSeconds > 9)
	{
		MSecondsText = FString::FromInt(MSeconds);
	}
	else
	{
		MSecondsText = "0" + FString::FromInt(MSeconds);
	}

	FString TimeConverted = MinutesText + ":" + SecondsText + "." + MSecondsText;
	return FText::FromString(TimeConverted);
}
