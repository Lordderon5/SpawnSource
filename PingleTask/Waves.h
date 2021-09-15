// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waves.generated.h"

UCLASS()
class PINGLETASK_API AWaves : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

public:	
	// Sets default values for this actor's properties
	AWaves();
	// Creating Spawn Parameters. Making them EditAnyWhere to get access from Editor

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 500.0f, ClampMin = 25.0f))
		float SpawnRadius = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 50.0f, ClampMin = 5.0f))
		float MinSpawnRadius = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 20.0f, ClampMin = 5.0f))
		float EnemyRadius = 80.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 1, ClampMin = 1))
		int32 WaveEnemies = 20;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 1, ClampMin = 1))
		int32 WaveLimit = 10;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 0.01f, ClampMin = 0.01f))
		float WaveEnemiesIncrease = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (UIMin = 0.1f, ClampMin = 0.1f))
		float SpawnRadiusIncrease = 0.05f;

	//Create WaveCounter for HUD
	static int Wave;
	//Array to keep Coordinates of Spawn Enemies
	TArray <FVector> Coordinates;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector RandVec();

	UFUNCTION()
		void Spawn();

	bool IsValid(FVector Coords);

	void NewWave();

	void AddWave();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
		static int GetWave();

	static void SetWave();

};
