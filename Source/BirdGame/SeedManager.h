// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SeedManager.generated.h"

class UMaterialInterface;

UCLASS()
class BIRDGAME_API ASeedManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeedManager();

	// Called every frame
	// TODO: Should probably be turned off if no seeds are actively spawning, though it might not matter since seeds will be constantly spawning late game
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SpawnExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* SeedMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInstancedStaticMeshComponent* SeedMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoundsBox;

private:
	float TimeSinceLastSpawn;
};
