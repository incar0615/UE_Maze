// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeExit.h"


// Sets default values
AMazeExit::AMazeExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("asdqwe"));
	RootComponent = staticMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CUBE(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Exit.Exit'"));
	staticMesh->SetStaticMesh(CUBE.Object);
	staticMesh->SetMaterial(0, Material.Object);
	staticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Tags.Add(FName("Exit"));
}

// Called when the game starts or when spawned
void AMazeExit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

