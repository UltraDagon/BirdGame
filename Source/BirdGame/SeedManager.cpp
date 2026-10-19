// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedManager.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ASeedManager::ASeedManager()
	: SpawnExtent(50.0f)
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
	SeedMesh->NumCustomDataFloats = 8; // StartPos(3), TargetPos(3), SpawnTime(1), DurationTime(1)
	SeedMesh->SetupAttachment(RootComponent);
	SeedMesh->SetMobility(EComponentMobility::Movable); // maybe not needed

	SeedMesh->SetCastShadow(false);
	SeedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SeedMesh->SetBoundsScale(100.0f);

	// TODO: Make this a UPROPERTY
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		SeedMesh->SetStaticMesh(SphereMeshAsset.Object);
		SeedMesh->SetRelativeScale3D(FVector(0.1f));
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

	SeedMesh->SetCustomData(
		SeedMesh->AddInstance(FTransform(FVector(0, 0, 0))),
		TArray<float>({ 0,0,50, 0,0,-50, 10.0f, 5.0f }),
		false);

	SeedMesh->SetCustomData(
		SeedMesh->AddInstance(FTransform(FVector(0, 0, 0))),
		TArray<float>({ 0,0,50, 50,50,-50, 5.0f, 5.0f }),
		true);

}

// Called every frame
void ASeedManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

