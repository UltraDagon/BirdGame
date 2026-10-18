// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraDirector.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMainCameraDirector::AMainCameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);

	bActivateOnStart = true;
}

// Called when the game starts or when spawned
void AMainCameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
    if (bActivateOnStart)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (PlayerController)
        {
            PlayerController->SetViewTargetWithBlend(this, 0.0f);
        }
    }
}

// Called every frame
void AMainCameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

