// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeWall.h"
#include "MazeGenerator.generated.h"

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
		int MapSize;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
