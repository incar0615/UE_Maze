// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeWall.h"
#include "MazeBlock.h"
#include "MazeDoor.h"
#include "MazeExit.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */

enum TileState
{
	EMPTY = 0, WALL, ROOM, CORRIDOR, DOOR,
};

enum Direction {
	EAST = 0, WEST, NORTH, SOUTH
};


UCLASS()
class JCH_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int maxRoom = 15;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int MapSize = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int MaxMapSize = 100;

	bool firstGen = true;

	UPROPERTY()
		TArray<int> wallTilelist;

	UPROPERTY()
		TArray<AMazeWall*> wallPool;

	UPROPERTY()
		TArray<AMazeDoor*> doorPool;

	UPROPERTY()
		TArray<AMazeBlock*> blockPool;

	UPROPERTY()
		AMazeExit * ExitObj;
	UPROPERTY()
		AMazeWall* root;

	TileState tileMap[250][250];



	int roomCnt;
	void GenerateDungeon();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void GenerateDungeon2(int _roomNumber, int _mapSize);
	void MakeRoom(int _tileNum);
};
