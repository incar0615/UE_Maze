// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rComponent"));
	RootComponent = rCompo;
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0,0,0);
	const int a = MapSize;
	bool mapState[100][100];

	for (int y = 0; y < MapSize; y++) {
		for (int x = 0; x < MapSize; x++) {
			if (x == 0 || x == MapSize - 1 || y == 0 || y == MapSize - 1) {
				mapState[x][y] = false;							// �����ڸ��� ������ �������
			}
			else if (x % 2 == 0 && y % 2 == 0) {		//  X �� Y �� �����ϴ� 2�� ��� ĭ���� ������ �������
				mapState[x][y] = false;
			}
			else {
				mapState[x][y] = true;					// ���� ĭ�� ��ĭ����
			}
		}
	}
	
	for (int y = 2; y < MapSize - 1; y += 2) {
		for (int x = 2; x < MapSize - 1; x += 2) {

			switch (rand() % 4)
			{
			case 0:
				mapState[x + 1][y] = false;
				break;
			case 1:
				mapState[x - 1][y] = false;
				break;
			case 2:
				mapState[x][y + 1] = false;
				break;
			case 3:
				mapState[x][y - 1] = false;
				break;
			}
		}
	}

	if (World)
	{
		for (int y = 0; y < MapSize; y++) {
			for (int x = 0; x < MapSize; x++) {
				if(!mapState[x][y])
				World->SpawnActor<AMazeWall>(AMazeWall::StaticClass(), FVector(x * 100,y*100,50), myRot, SpawnInfo);
			}
		}
	}
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

