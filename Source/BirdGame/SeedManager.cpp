// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedManager.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ASeedManager::ASeedManager()
	: SpawnExtent(50.0f)
	, TimeSinceLastSpawn(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	BoundsBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundsBox"));
	BoundsBox->SetupAttachment(RootComponent);
	BoundsBox->SetBoxExtent(SpawnExtent);
	BoundsBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoundsBox->SetHiddenInGame(true);

	SeedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SeedMesh"));
	SeedMesh->NumCustomDataFloats = 5; // TargetPos(3), SpawnTime(1), DurationTime(1)
	SeedMesh->SetupAttachment(RootComponent);

	SeedMesh->SetCastShadow(true); // Disable for performance
	SeedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// TODO: Make this a UPROPERTY
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		SeedMesh->SetStaticMesh(SphereMeshAsset.Object);
		SeedMesh->SetRelativeScale3D(FVector(0.1f));
	}
}

// Handle updates from the editor
void ASeedManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (BoundsBox)
	{
		BoundsBox->SetBoxExtent(FVector(SpawnExtent));
		BoundsBox->UpdateBounds();
	}
}

// Called when the game starts or when spawned
void ASeedManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (SeedMaterial)
	{
		SeedMesh->SetMaterial(0, SeedMaterial);
	}

	// Should be param with visual
	SeedMesh->SetCustomPrimitiveDataVector3f(0, FVector3f(SpawnExtent.X, 0, 0)); // StartPos
}

// Called every frame
void ASeedManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Sx = SpawnExtent.X;
	const float Sy = SpawnExtent.Y;
	const float Sz = SpawnExtent.Z;
	const float SpawnRate = 1.0f;

	TimeSinceLastSpawn += DeltaTime;

	while (TimeSinceLastSpawn >= SpawnRate) {
		TimeSinceLastSpawn -= SpawnRate;

		SeedMesh->SetCustomData(
			SeedMesh->AddInstance(FTransform(FVector(0, 0, 0))),
			TArray<float>({
				FMath::FRandRange(-1.0f, 1.0f) * Sx,
				FMath::FRandRange(-1.0f, 1.0f) * Sy,
				-Sz,
				(float)GetWorld()->GetTimeSeconds(),
				1.0f // TODO: Duration should eventually be constant. If it isn't, will need to make sure arc height is lower
			}), true
		);
	}

	//GEngine->AddOnScreenDebugMessage(0, 0.0f, FColor::Green, FString::Printf(TEXT("World Time: %.2f s"), GetWorld()->GetTimeSeconds()));
}

