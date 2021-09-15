// Fill out your copyright notice in the Description page of Project Settings.

// Note: Actually I tried to use GameMode instead of Actor, but the game mode did'n create new Waves. You can see the code of it at WaveMode.cpp
#include "Waves.h"
#include "Engine/World.h"
#include "Enemy.h"

int AWaves::Wave;

// Sets default values
AWaves::AWaves()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create the static mesh to add this Actor to the location
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	// Set initial values
	SetWave();
	AEnemy::SetDeadEnemies();
	AEnemy::SetScore();
}

// Called when the game starts or when spawned
void AWaves::BeginPlay()
{
	Super::BeginPlay();
	AddWave();
	NewWave();
}

// Called every frame
void AWaves::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Checking if the player kill enough enemies to create a new wave
	if ((AEnemy::GetDeadEnemies() % WaveLimit == 0) && (AEnemy::GetDeadEnemies() != 0))
	{
		// Increasing amount of enemies to spawn and spawn radius
		WaveEnemies = WaveEnemies + WaveEnemies * WaveEnemiesIncrease;
		SpawnRadius = SpawnRadius + SpawnRadius * SpawnRadiusIncrease;
		NewWave();

		// Increase wave counter for HUD
		AddWave();

		// Set the counter back to zero
		AEnemy::SetDeadEnemies();
	}
}


// Spawn function
void AWaves::Spawn()
{
	// Get the current world
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;

		// Create a random enemy location based on current player location
		FVector Loc = RandVec();

		world->SpawnActor<AEnemy>(Loc, FRotator::ZeroRotator, spawnParams);
	}
}
// Generate a new enemy location
FVector AWaves::RandVec()
{
	FVector RandomVector = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	float yRange, xRange;
	xRange = FMath::FRandRange(MinSpawnRadius, SpawnRadius);
	yRange = FMath::FRandRange(MinSpawnRadius, FMath::Sqrt(FMath::Square(SpawnRadius) - FMath::Square(xRange)));
	RandomVector.X += xRange;
	RandomVector.Y += yRange;
	RandomVector.Z = 100.0f;
	return RandomVector;
}

// This should be coordination validate, but I had an endless cycle in RandVec instead
bool AWaves::IsValid(FVector Coords)
{
	int size = Coordinates.GetAllocatedSize() / sizeof(FVector);
	for (int i = 0; i < size; i++)
	{
		if (FMath::Abs(FVector::Dist2D(Coordinates[i], Coords)) < 80)
			return false;
	}
//	Coordinates.Add(Coords);
	return true;
}

// Spawn the specified number of enemies
void AWaves::NewWave()
{
	int i = 0;
	while (i < WaveEnemies)
	{
		Spawn();
		i++;
	}
}

void AWaves::AddWave()
{
	Wave++;
}

int AWaves::GetWave()
{
	return Wave;
}

void AWaves::SetWave()
{
	Wave = 0;
}