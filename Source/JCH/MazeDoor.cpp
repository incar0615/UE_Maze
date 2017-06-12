// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeDoor.h"


// Sets default values
AMazeDoor::AMazeDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = staticMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CUBE(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Door.Door'"));
	staticMesh->SetStaticMesh(CUBE.Object);
	staticMesh->SetRelativeScale3D(FVector(1, 1, 1.5));
	staticMesh->SetMaterial(0, Material.Object);
	
}

// Called when the game starts or when spawned
void AMazeDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

