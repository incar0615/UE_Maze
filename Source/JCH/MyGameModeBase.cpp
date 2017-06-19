// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"




void AMyGameModeBase::GenerateDungeon()
{
}

void AMyGameModeBase::GenerateDungeon2(int _roomNumber, int _mapSize)
{
	maxRoom = _roomNumber;
	MapSize = MaxMapSize = _mapSize;
	
	roomCnt = 1;

	UWorld* const World = GetWorld();
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);

	const int startPos = MapSize*0.5f;
	int randomFactor = rand() % 4 + 2;
	int wallCnt = 0, doorCnt = 0, blockCnt = 0;

	
	if (firstGen) {
		root = World->SpawnActor<AMazeWall>(AMazeWall::StaticClass(), FVector(MapSize * 50.0f, MapSize * 50.0f, 64), myRot, SpawnInfo);
		root->SetActorHiddenInGame(true);
		root->SetActorEnableCollision(false);

		ExitObj = World->SpawnActor<AMazeExit>(AMazeExit::StaticClass(), FVector(0, 0, 10000), myRot, SpawnInfo);
		ExitObj->AttachRootComponentToActor(root);

		for (int i = 0; i <1000; i++) {
			AMazeWall* wall = World->SpawnActor<AMazeWall>(AMazeWall::StaticClass(), FVector( 0, 0, 10000), myRot, SpawnInfo);
			wall->AttachRootComponentToActor(root);
			//wall->SetActorHiddenInGame(true);
			wallPool.Add(wall);
		}
		for (int i = 0; i <200; i++) {
			AMazeDoor* door = World->SpawnActor<AMazeDoor>(AMazeDoor::StaticClass(), FVector(0, 0, 10000), myRot, SpawnInfo);
			door->AttachRootComponentToActor(root);
			//door->SetActorHiddenInGame(true);
			doorPool.Add(door);

			AMazeBlock* block = World->SpawnActor<AMazeBlock>(AMazeBlock::StaticClass(), FVector(0, 0, 10000), myRot, SpawnInfo);
			block->AttachRootComponentToActor(root);
			//block->SetActorHiddenInGame(true);
			blockPool.Add(block);
		}
	
		
		firstGen = false;
	}
	else {
		for (int i = 0; i <1000; i++) {
			wallPool[i]->SetActorLocation(FVector(0, 0, 10000));
			//wallPool[i]->SetActorHiddenInGame(true);
		}
		for (int i = 0; i <200; i++) {
			blockPool[i]->SetActorLocation(FVector(0, 0, 10000));
			//blockPool[i]->SetActorHiddenInGame(true);

			doorPool[i]->SetActorLocation(FVector(0, 0, 10000));
			//doorPool[i]->SetActorHiddenInGame(true);
		}
		wallTilelist.Empty();

		//TArray<AActor*> pawn;
		//AMyPawn* myPawn;
		//UGameplayStatics::GetAllActorsOfClass(World, AMyPawn::StaticClass(), pawn);
		//
		//myPawn = (AMyPawn*)pawn[0];
		//myPawn->Movement->SetActive(false);
		//myPawn->TeleportTo(root->GetActorLocation(),root->GetActorRotation(),false,false);
		//myPawn->SetActorLocation(root->GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
	}
	
	
	
	
	// 타일을 모두 빈칸으로 초기화
	for (int y = 0; y < MapSize; y++) {
		for (int x = 0; x < MapSize; x++) {
			tileMap[x][y] = TileState::EMPTY;
		}
	}
	
	// 맵 한가운데에 방을 생성
	for (int y = startPos - randomFactor; y < startPos + randomFactor + 1; y++) {
		for (int x = startPos - randomFactor; x < startPos + randomFactor + 1; x++) {
			// 구석은 복도 생성을 막기 위해서 예외처리
			if (x == startPos - randomFactor && y == startPos - randomFactor ||
				x == startPos - randomFactor && y == startPos + randomFactor ||
				x == startPos + randomFactor && y == startPos - randomFactor ||
				x == startPos + randomFactor && y == startPos + randomFactor) {
				tileMap[x][y] = TileState::WALL;
			}
			// 벽타일
			else if (x == startPos - randomFactor || x == startPos + randomFactor || y == startPos - randomFactor || y == startPos + randomFactor) {
				wallTilelist.Add(x * 1000 + y);
				tileMap[x][y] = TileState::WALL;
			}
			// 방타일
			else {
				tileMap[x][y] = TileState::ROOM;
			}

		}
	}
	int cnt = 0;

	// 방 만들기
	while (roomCnt < maxRoom && cnt < 300) {
		cnt++;
		MakeRoom(wallTilelist[rand() % (int)wallTilelist.Num()]);
	}
	int exitTile = rand() % (int)wallTilelist.Num();
	int exitX = wallTilelist[exitTile] / 1000 , exitY = wallTilelist[exitTile] % 1000;;
	ExitObj->SetActorLocation(FVector(wallTilelist[exitTile] / 10, (wallTilelist[exitTile] % 1000) * 100, 0));
	tileMap[exitX][exitY] = TileState::EMPTY;

	if (World)
	{
		for (int y = 0; y < MapSize; y++) {
			for (int x = 0; x < MapSize; x++) {
				//if (tileMap[x][y] == TileState::CORRIDOR || tileMap[x][y] == TileState::ROOM)
			
				if (tileMap[x][y] == TileState::WALL) {
					//wallPool[wallCnt]->SetActorHiddenInGame(false);
					wallPool[wallCnt]->SetActorLocation(FVector(x * 100, y * 100, 50));

					wallCnt++;
				}
				else if (tileMap[x][y] == TileState::CORRIDOR) {
					//blockPool[blockCnt]->SetActorHiddenInGame(false);
					blockPool[blockCnt]->SetActorLocation(FVector(x * 100, y * 100, 50));
					blockCnt++;
				}
				
				else if (tileMap[x][y] == TileState::DOOR) {
					//doorPool[doorCnt]->SetActorHiddenInGame(false);
					doorPool[doorCnt]->SetActorLocation(FVector(x * 100, y * 100, 50));
					doorCnt++;
				}
					
			}
		}
	}
	
}

void AMyGameModeBase::MakeRoom(int _tileNum)
{
	
	int r = rand() % 6 + 3;
	int roomSize = rand() % 5 + 4;
	switch (rand() % 4)
	{
	case Direction::EAST:

		for (int i = 1; i < r; i++) {
			if (_tileNum / 1000 + i > MaxMapSize) return;
			if (tileMap[_tileNum / 1000 + i][_tileNum % 1000] != TileState::EMPTY) return;
		}
		for (int y = -roomSize; y < roomSize + 1; y++) {
			for (int x = 0; x < roomSize * 2; x++) {
				if (_tileNum / 1000 + r + x > MaxMapSize || _tileNum % 1000 + y > MaxMapSize || _tileNum % 1000 + y < 0)return;
				if (tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] != TileState::EMPTY) return;
			}
		}
		for (int i = 1; i < r; i++) {
			tileMap[_tileNum / 1000 + i][_tileNum % 1000 + 1] = TileState::CORRIDOR;
			tileMap[_tileNum / 1000 + i][_tileNum % 1000 - 1] = TileState::CORRIDOR;
		}
		for (int y = -roomSize; y < roomSize + 1; y++) {
			for (int x = 0; x < roomSize * 2; x++) {
				if (x == 0 && y == roomSize ||
					x == 0 && y == -roomSize ||
					x == roomSize * 2 - 1 && y == roomSize ||
					x == roomSize * 2 - 1 && y == -roomSize) {
					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::WALL;
				}
				else if (x == 0 || x == roomSize * 2 - 1 || y == -roomSize || y == roomSize) {
					wallTilelist.Add((_tileNum / 1000 + r + x) * 1000 + (_tileNum % 1000 + y));
					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::WALL;
				}
				else
					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::ROOM;
			}
		}
		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
		tileMap[_tileNum / 1000 + r][_tileNum % 1000] = TileState::DOOR;

		roomCnt++;

		wallTilelist.RemoveAt(wallTilelist.Find(_tileNum));
		break;

	case Direction::WEST:
		for (int i = 1; i < r; i++) {
			if (_tileNum / 1000 - i < 0) return;
			if (tileMap[_tileNum / 1000 - i][_tileNum % 1000] != TileState::EMPTY) return;
		}
		for (int y = -roomSize; y < roomSize + 1; y++) {
			for (int x = 0; x < roomSize * 2; x++) {
				if (_tileNum / 1000 - r - x < 0 || _tileNum % 1000 + y > MaxMapSize || _tileNum % 1000 + y < 0)return;
				if (tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] != TileState::EMPTY) return;
			}
		}

		for (int i = 1; i < r; i++) {
			tileMap[_tileNum / 1000 - i][_tileNum % 1000 + 1] = TileState::CORRIDOR;
			tileMap[_tileNum / 1000 - i][_tileNum % 1000 - 1] = TileState::CORRIDOR;
		}
		for (int y = -roomSize; y < roomSize + 1; y++) {
			for (int x = 0; x < roomSize * 2; x++) {
				if (x == 0 && y == roomSize ||
					x == 0 && y == -roomSize ||
					x == roomSize * 2 - 1 && y == roomSize ||
					x == roomSize * 2 - 1 && y == -roomSize) {
					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::WALL;
				}
				else if (x == 0 || x == roomSize * 2 - 1 || y == -roomSize || y == roomSize) {
					wallTilelist.Add((_tileNum / 1000 - r - x) * 1000 + (_tileNum % 1000 + y));
					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::WALL;
				}
				else
					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::ROOM;
			}
		}
		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
		tileMap[_tileNum / 1000 - r][_tileNum % 1000] = TileState::DOOR;
		roomCnt++;
		wallTilelist.RemoveAt(wallTilelist.Find(_tileNum));
		break;

	case Direction::NORTH:
		for (int i = 1; i < r; i++) {
			if (_tileNum % 1000 + i > MaxMapSize) return;
			if (tileMap[_tileNum / 1000][_tileNum % 1000 + i] != TileState::EMPTY) return;
		}
		for (int y = 0; y < roomSize * 2; y++) {
			for (int x = -roomSize; x < roomSize + 1; x++) {
				if (_tileNum % 1000 + r + y > MaxMapSize || _tileNum / 1000 + x > MaxMapSize || _tileNum / 1000 + x < 0)return;
				if (tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] != TileState::EMPTY) return;
			}
		}
		for (int i = 1; i < r; i++) {
			tileMap[_tileNum / 1000 + 1][_tileNum % 1000 + i] = TileState::CORRIDOR;
			tileMap[_tileNum / 1000 - 1][_tileNum % 1000 + i] = TileState::CORRIDOR;
		}
		for (int y = 0; y < roomSize * 2; y++) {
			for (int x = -roomSize; x < roomSize + 1; x++) {
				if (y == 0 && x == roomSize ||
					y == 0 && x == -roomSize ||
					y == roomSize * 2 - 1 && x == roomSize ||
					y == roomSize * 2 - 1 && x == -roomSize) {
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::WALL;
				}
				else if (y == 0 || y == roomSize * 2 - 1 || x == -roomSize || x == roomSize) {
					wallTilelist.Add((_tileNum / 1000 + x) * 1000 + (_tileNum % 1000 + r + y));
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::WALL;
				}
				else
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::ROOM;
			}
		}
		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
		tileMap[_tileNum / 1000][_tileNum % 1000 + r] = TileState::DOOR;
		roomCnt++;
		wallTilelist.RemoveAt(wallTilelist.Find(_tileNum));
		break;

	case Direction::SOUTH:
		for (int i = 1; i < r; i++) {
			if (_tileNum % 1000 - 1 < 0) return;;
			if (tileMap[_tileNum / 1000][_tileNum % 1000 - i] != TileState::EMPTY) return;
		}
		for (int y = 0; y < roomSize * 2; y++) {
			for (int x = -roomSize; x < roomSize + 1; x++) {
				if (_tileNum % 1000 - r - y < 0 || _tileNum / 1000 + x > MaxMapSize || _tileNum / 1000 + x < 0)return;
				if (tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] != TileState::EMPTY) return;
			}
		}
		for (int i = 1; i < r; i++) {
			tileMap[_tileNum / 1000 + 1][_tileNum % 1000 - i] = TileState::CORRIDOR;
			tileMap[_tileNum / 1000 - 1][_tileNum % 1000 - i] = TileState::CORRIDOR;
		}
		for (int y = 0; y < roomSize * 2; y++) {
			for (int x = -roomSize; x < roomSize + 1; x++) {
				if (y == 0 && x == roomSize ||
					y == 0 && x == -roomSize ||
					y == roomSize * 2 - 1 && x == roomSize ||
					y == roomSize * 2 - 1 && x == -roomSize) {
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::WALL;
				}
				else if (y == 0 || y == roomSize * 2 - 1 || x == -roomSize || x == roomSize) {
					wallTilelist.Add((_tileNum / 1000 + x) * 1000 + (_tileNum % 1000 - r - y));
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::WALL;
				}
				else
					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::ROOM;
			}
		}
		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
		tileMap[_tileNum / 1000][_tileNum % 1000 - r] = TileState::DOOR;
		roomCnt++;

		wallTilelist.RemoveAt(wallTilelist.Find(_tileNum));
		
		break;
	}
}
