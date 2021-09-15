// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class PINGLETASK_API AEnemy : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY()
		class UParticleSystem* DestroyParticleSystem;
	//Counter of dead enemies to create a new Wave
	static int DeathCounter;
	//Score for the HUD
	static int Score;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDeathCount();

	static int GetDeadEnemies();

	static void SetDeadEnemies();

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	static void SetScore();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
		static int GetScore();

};
