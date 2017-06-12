// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeWall.h"


// Sets default values
AMazeWall::AMazeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	RootComponent = staticMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CUBE(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	staticMesh->SetStaticMesh(CUBE.Object);
	staticMesh->SetRelativeScale3D(FVector(1, 1, 1.5));
}

// Called when the game starts or when spawned
void AMazeWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

