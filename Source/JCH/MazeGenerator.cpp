//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "MazeGenerator.h"
//
//
//// Sets default values
//AMazeGenerator::AMazeGenerator()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	rCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rComponent"));
//	RootComponent = rCompo;
//}
//
//// Called when the game starts or when spawned
//void AMazeGenerator::BeginPlay()
//{
//	Super::BeginPlay();
//	roomCnt = 1;
//	GenerateDungeon2();
//}
//
//// Called every frame
//void AMazeGenerator::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}
//
//void AMazeGenerator::GenerateDungeon() {
//	UWorld* const World = GetWorld();
//	FActorSpawnParameters SpawnInfo;
//	FRotator myRot(0, 0, 0);
//	const int a = MapSize;
//	bool mapState[100][100];
//
//	for (int y = 0; y < MapSize; y++) {
//		for (int x = 0; x < MapSize; x++) {
//			if (x == 0 || x == MapSize - 1 || y == 0 || y == MapSize - 1) {
//				mapState[x][y] = false;							// 가장자리를 벽으로 만들어줌
//			}
//			else if (x % 2 == 0 && y % 2 == 0) {		//  X 와 Y 가 교차하는 2의 배수 칸마다 벽으로 만들어줌
//				mapState[x][y] = false;
//			}
//			else {
//				mapState[x][y] = true;					// 남은 칸은 빈칸으로
//			}
//		}
//	}
//
//	for (int y = 2; y < MapSize - 1; y += 2) {
//		for (int x = 2; x < MapSize - 1; x += 2) {
//
//			switch (rand() % 4)
//			{
//			case 0:
//				mapState[x + 1][y] = false;
//				break;
//			case 1:
//				mapState[x - 1][y] = false;
//				break;
//			case 2:
//				mapState[x][y + 1] = false;
//				break;
//			case 3:
//				mapState[x][y - 1] = false;
//				break;
//			}
//		}
//	}
//
//	if (World)
//	{
//		for (int y = 0; y < MapSize; y++) {
//			for (int x = 0; x < MapSize; x++) {
//				if (!mapState[x][y])
//					World->SpawnActor<AMazeWall>(AMazeWall::StaticClass(), FVector(x * 100, y * 100, 50), myRot, SpawnInfo);
//			}
//		}
//	}
//}
//void AMazeGenerator::GenerateDungeon2() {
//	UWorld* const World = GetWorld();
//	FActorSpawnParameters SpawnInfo;
//	FRotator myRot(0, 0, 0);
//	
//	const int startPos = MapSize*0.5f;
//	int randomFactor = rand() % 4 +2;
//
//	// 타일을 모두 빈칸으로 초기화
//	for (int y = 0; y < MapSize; y++) {
//		for (int x = 0; x < MapSize; x++) {
//			tileMap[x][y] = TileState::EMPTY;
//		}
//	}
//
//	// 맵 한가운데에 방을 생성
//	for (int y = startPos - randomFactor; y < startPos + randomFactor+1; y++) {
//		for (int x = startPos - randomFactor; x < startPos + randomFactor+1; x++) {
//			// 구석은 복도 생성을 막기 위해서 예외처리
//			if (x == startPos - randomFactor && y == startPos - randomFactor ||
//				x == startPos - randomFactor && y == startPos + randomFactor ||
//				x == startPos + randomFactor && y == startPos - randomFactor || 
//				x == startPos + randomFactor && y == startPos + randomFactor) {
//				tileMap[x][y] = TileState::WALL;
//			}
//			// 벽타일
//			else if (x == startPos - randomFactor || x == startPos + randomFactor || y == startPos - randomFactor || y == startPos + randomFactor) {
//				wallTilelist.Add(x * 1000 + y);	
//				tileMap[x][y] = TileState::WALL;
//			}
//			// 방타일
//			else {
//				tileMap[x][y] = TileState::ROOM;
//			}
//			
//		}
//	}
//	int cnt = 0;
//
//	// 방 만들기
//	while (roomCnt < maxRoom && cnt < 300) {
//		cnt++;
//		MakeRoom(wallTilelist[rand() % (int)wallTilelist.Num()]);
//	}
//	
//
//
//	if (World)
//	{
//		for (int y = 0; y < MapSize; y++) {
//			for (int x = 0; x < MapSize; x++) {
//				//if (tileMap[x][y] == TileState::CORRIDOR || tileMap[x][y] == TileState::ROOM)
//				if (tileMap[x][y] == TileState::WALL) {
//					World->SpawnActor<AMazeWall>(AMazeWall::StaticClass(), FVector(x * 100, y * 100, 50), myRot, SpawnInfo);
//				}
//				else if (tileMap[x][y] == TileState::CORRIDOR) 	
//					World->SpawnActor<AMazeBlock>(AMazeBlock::StaticClass(), FVector(x * 100, y * 100, 50), myRot, SpawnInfo);
//				else if (tileMap[x][y] == TileState::DOOR)
//					World->SpawnActor<AMazeDoor>(AMazeDoor::StaticClass(), FVector(x * 100, y * 100, 50), myRot, SpawnInfo);
//			}
//		}
//	}
//}
//
//void AMazeGenerator::MakeRoom(int _tileNum) {
//
//	int r = rand() % 6 + 3;
//	int roomSize = rand() % 4 + 2;
//	switch (rand()%4)
//	{
//	case Direction::EAST:
//		
//		for(int i = 1; i < r; i++) {
//			if (_tileNum / 1000 + i > MaxMapSize) return;
//			if (tileMap[_tileNum / 1000 + i][_tileNum % 1000] != TileState::EMPTY) return;
//		}
//		for (int y = -roomSize; y < roomSize +1; y++) {
//			for (int x = 0; x < roomSize*2; x++) {
//				if (_tileNum / 1000 + r + x > MaxMapSize || _tileNum % 1000 + y > MaxMapSize || _tileNum % 1000 + y < 0)return;
//				if (tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] != TileState::EMPTY) return;
//			}
//		}
//		for (int i = 1; i < r; i++) {
//			tileMap[_tileNum / 1000 + i][_tileNum % 1000] = TileState::CORRIDOR;
//		}
//		for (int y = -roomSize; y < roomSize +1; y++) {
//			for (int x = 0; x < roomSize*2; x++) {
//				if (x == 0 && y == roomSize ||
//					x == 0 && y == -roomSize ||
//					x == roomSize * 2 - 1 && y == roomSize ||
//					x == roomSize * 2 - 1 && y == -roomSize) {
//					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::WALL;
//				}
//				else if (x == 0 || x == roomSize*2 - 1 || y == -roomSize || y == roomSize) {
//					wallTilelist.Add((_tileNum / 1000 + r + x) * 1000 + (_tileNum % 1000 + y));
//					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::WALL;
//				}
//				else
//					tileMap[_tileNum / 1000 + r + x][_tileNum % 1000 + y] = TileState::ROOM;
//			}
//		}
//		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
//		tileMap[_tileNum / 1000 + r][_tileNum % 1000] = TileState::DOOR;
//
//		roomCnt++;
//		break;
//
//	case Direction::WEST:
//		for (int i = 1; i < r; i++) {
//			if (_tileNum / 1000 - i < 0) return;
//			if (tileMap[_tileNum / 1000 - i][_tileNum % 1000] != TileState::EMPTY) return;
//		}
//		for (int y = -roomSize; y < roomSize + 1; y++) {
//			for (int x = 0; x < roomSize*2; x++) {
//				if (_tileNum / 1000 - r - x < 0 || _tileNum % 1000 + y > MaxMapSize || _tileNum % 1000 + y < 0)return;
//				if (tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] != TileState::EMPTY) return;
//			}
//		}
//
//		for (int i = 1; i < r; i++) {
//			tileMap[_tileNum / 1000 - i][_tileNum % 1000] = TileState::CORRIDOR;
//		}
//		for (int y = -roomSize; y < roomSize + 1; y++) {
//			for (int x = 0; x < roomSize*2; x++) {
//				if (x == 0 && y == roomSize ||
//					x == 0 && y == -roomSize ||
//					x == roomSize * 2 - 1 && y == roomSize ||
//					x == roomSize * 2 - 1 && y == -roomSize) {
//					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::WALL;
//				}
//				else if (x == 0 || x == roomSize*2 - 1 || y == -roomSize || y == roomSize) {
//					wallTilelist.Add((_tileNum / 1000 - r - x) * 1000 + (_tileNum % 1000 + y));
//					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::WALL;
//				}
//				else
//					tileMap[_tileNum / 1000 - r - x][_tileNum % 1000 + y] = TileState::ROOM;
//			}
//		}
//		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
//		tileMap[_tileNum / 1000 - r][_tileNum % 1000] = TileState::DOOR;
//		roomCnt++;
//		break;
//
//	case Direction::NORTH:
//		for (int i = 1; i < r; i++) {
//			if (_tileNum % 1000 + i > MaxMapSize) return;
//			if (tileMap[_tileNum / 1000][_tileNum % 1000 + i] != TileState::EMPTY) return;
//		}
//		for (int y = 0; y < roomSize*2; y++) {
//			for (int x = -roomSize ; x < roomSize  +1; x++) {
//				if (_tileNum % 1000 + r + y > MaxMapSize || _tileNum / 1000 + x > MaxMapSize || _tileNum / 1000 + x < 0)return;
//				if (tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] != TileState::EMPTY) return;
//			}
//		}
//		for (int i = 1; i < r; i++) {
//			tileMap[_tileNum / 1000][_tileNum % 1000 + i] = TileState::CORRIDOR;
//		}
//		for (int y = 0; y < roomSize*2; y++) {
//			for (int x = -roomSize ; x < roomSize  + 1; x++) {
//				if (y == 0 && x == roomSize ||
//					y == 0 && x == -roomSize ||
//					y == roomSize * 2 - 1 && x == roomSize ||
//					y == roomSize * 2 - 1 && x == -roomSize) {
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::WALL;
//				}
//				else if (y == 0 || y == roomSize*2 - 1 || x == -roomSize || x == roomSize) {
//					wallTilelist.Add((_tileNum / 1000 + x) * 1000 + (_tileNum % 1000 + r + y));
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::WALL;
//				}
//				else 
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 + r + y] = TileState::ROOM;
//			}
//		}
//		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
//		tileMap[_tileNum / 1000][_tileNum % 1000+r] = TileState::DOOR;
//		roomCnt++;
//		break;
//
//	case Direction::SOUTH:
//		for (int i = 1; i < r; i++) {
//			if (_tileNum % 1000 - 1 < 0) return;;
//			if (tileMap[_tileNum / 1000][_tileNum % 1000 - i] != TileState::EMPTY) return;
//		}
//		for (int y = 0; y < roomSize*2; y++) {
//			for (int x = -roomSize ; x < roomSize  + 1; x++) {
//				if (_tileNum % 1000 - r - y < 0 || _tileNum / 1000 + x > MaxMapSize || _tileNum / 1000 + x < 0)return;
//				if (tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] != TileState::EMPTY) return;
//			}
//		}
//		for (int i = 1; i < r; i++) {
//			tileMap[_tileNum / 1000][_tileNum % 1000 - i] = TileState::CORRIDOR;
//		}
//		for (int y = 0; y < roomSize*2; y++) {
//			for (int x = -roomSize ; x < roomSize  + 1; x++) {
//				if (y == 0 && x == roomSize ||
//					y == 0 && x == -roomSize ||
//					y == roomSize * 2 - 1 && x == roomSize ||
//					y == roomSize * 2 - 1 && x == -roomSize) {
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::WALL;
//				}
//				else if (y == 0 || y == roomSize*2 - 1 || x == -roomSize || x == roomSize) {
//					wallTilelist.Add((_tileNum / 1000 + x) * 1000 + (_tileNum % 1000 - r - y));
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::WALL;
//				}
//				else 
//					tileMap[_tileNum / 1000 + x][_tileNum % 1000 - r - y] = TileState::ROOM;
//			}
//		}
//		tileMap[_tileNum / 1000][_tileNum % 1000] = TileState::DOOR;
//		tileMap[_tileNum / 1000][_tileNum % 1000 -r] = TileState::DOOR;
//		roomCnt++;
//		break;
//	}
//}
//
