// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "MazeWall.generated.h"

UCLASS()
class JCH_API AMazeWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeWall();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "asd")
		class UStaticMeshComponent* staticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
