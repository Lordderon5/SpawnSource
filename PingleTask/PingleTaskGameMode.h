// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingleTaskGameMode.generated.h"


UCLASS(minimalapi)
class APingleTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()
		
	virtual void BeginPlay() override; //Override BeginPlay from the base class

public:
	APingleTaskGameMode();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> ScoreHUD;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
};



