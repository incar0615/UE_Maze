// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MyGameModeBase.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class JCH_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
		class UCapsuleComponent* Body;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
		class UStaticMeshComponent* staticMesh;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UFloatingPawnMovement* Movement;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class USphereComponent* SphereCollision;

	float CurrentLeftRightVal;
	float CurrentUpDownVal;
	float CurrentZoomInOutValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int maxRoom = 15;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map")
		int mapSize = 100;

	UFUNCTION()
	void MovementActive() {
		Movement->Velocity.Set(0, 0, 0);
		Movement->SetActive(true);
	}
	UFUNCTION()
	void LeftRight(float newInputValue);
	UFUNCTION()
	void UpDown(float newInputValue);
	UFUNCTION()
		void ZoomIO(float newInputValue);
	
	UFUNCTION()
		void InterAction(float newInputValue);
	UFUNCTION()
		void DeactiveInterAction();
	UFUNCTION()
		void Exit();

	UFUNCTION()
		void overlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void overlapDoor(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle timerHandle , interActionHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
