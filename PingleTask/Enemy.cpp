// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/WorldPSCPool.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Make the static variables accessable in the methods
int AEnemy::DeathCounter;
int AEnemy::Score;

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Creating a static mesh for this Actor
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Create a particle system

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	DestroyParticleSystem = ParticleAsset.Object;
	// Create a HitComponent system
	VisualMesh->SetNotifyRigidBodyCollision(true);

	VisualMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	VisualMesh->OnComponentHit.AddUniqueDynamic(this, &AEnemy::OnCompHit);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make the sphere fly and rotate
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

// Increase DeathCounter and Score
void AEnemy::AddDeathCount()
{
	DeathCounter++;
	Score++;
}

// Get the current value of DeathCounter 
int AEnemy::GetDeadEnemies()
{
	return DeathCounter;
}

// Set default value of DeathCounter
void AEnemy::SetDeadEnemies()
{
	DeathCounter = 0;
}

// Destroying the object on hit and increasing DeathCounter and Score
void AEnemy::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(OtherActor) && IsValid(OtherComp)) 
	{
//		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticleSystem, GetTransform(), true, EPSCPoolMethod::None, false);  Explosion effect
		AddDeathCount();
		Destroy(); // Destroy self if we hit anything
	}
}

// Set default value of Score
void AEnemy::SetScore()
{
	Score = 0;
}

// Get the current Score
int AEnemy::GetScore()
{
	return Score;
}

