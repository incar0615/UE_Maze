// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeWall.h"
#include "MazeBlock.h"
#include "MazeDoor.h"
#include "MazeGenerator.generated.h"


enum TileState
{
	EMPTY = 0, WALL, ROOM , CORRIDOR, DOOR,
};

enum Direction {
	EAST = 0 , WEST , NORTH , SOUTH
};

UCLASS()
class JCH_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Map")
		class UStaticMeshComponent* rCompo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int maxRoom = 6;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int MapSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int MaxMapSize;
	
	
	UPROPERTY()
		TArray<int> wallTilelist;
	
		//TileState* tileMap = new TileState[MapSize * MapsSize];
		TileState tileMap[250][250];
		
		int roomCnt;
	void GenerateDungeon();
	void GenerateDungeon2();
	void MakeRoom(int _tileNum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
