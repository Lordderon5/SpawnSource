// Copyright Epic Games, Inc. All Rights Reserved.

#include "PingleTaskGameMode.h"
#include "PingleTaskHUD.h"
#include "PingleTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

void APingleTaskGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Adding a Score HUD element
	if (ScoreHUD != nullptr)
	{
		CurrentWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), ScoreHUD));

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

APingleTaskGameMode::APingleTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APingleTaskHUD::StaticClass();
}
