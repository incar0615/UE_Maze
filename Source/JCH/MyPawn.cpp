// Fill out your copyright notice in the Description page of Project Settings.



#include "MyPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	RootComponent = Body;
	Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Body->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Body->SetCollisionProfileName("BlockAll");

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereCollision->SetupAttachment(Body);
	SphereCollision->SetRelativeLocation(FVector(50.0f, 0, 0));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CONE(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	staticMesh->SetStaticMesh(CONE.Object);
	staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Body);
	SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1200.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Body->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::overlapBegin);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::overlapDoor);
	Super::BeginPlay();
	AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameMode->GenerateDungeon2(maxRoom, mapSize);
	RootComponent->SetWorldLocation(MyGameMode->root->GetActorLocation(), false, NULL, ETeleportType::None);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector InputVector = FVector(CurrentUpDownVal, CurrentLeftRightVal, 0.0F);
	
	if (InputVector.SizeSquared() > 0.0F)
	{
		FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(InputVector);
		SetActorRotation(TargetRotation);
		if (Movement->IsActive()) {
			AddMovementInput(GetActorForwardVector());
		}
		
	}
	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LeftRight", this, &AMyPawn::LeftRight);
	PlayerInputComponent->BindAxis("UpDown", this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis("MouseClick", this, &AMyPawn::InterAction);
	PlayerInputComponent->BindAxis("ZoomInOut", this, &AMyPawn::ZoomIO);
}

void AMyPawn::LeftRight(float newInputValue) {
	CurrentLeftRightVal = newInputValue;
}

void AMyPawn::UpDown(float newInputValue) {
	CurrentUpDownVal = newInputValue;
}
void AMyPawn::ZoomIO(float newInputValue) {
	SpringArm->TargetArmLength += newInputValue*100;
}

void AMyPawn::InterAction(float newInputValue) {
	if (newInputValue > 0) {
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		FTimerDelegate timerdel;
		timerdel.BindUFunction(this, FName("DeactiveInterAction"));
		GetWorldTimerManager().SetTimer(interActionHandle, timerdel, 1.0f, false, 0.0f);
	}

}

void AMyPawn::Exit() {
	AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameMode->GenerateDungeon2(maxRoom , mapSize);
} 

void AMyPawn::overlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->Tags.Contains("Exit")) {
		AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		
		Movement->SetActive(false);
		RootComponent->SetWorldLocation(MyGameMode->root->GetActorLocation(), false, NULL, ETeleportType::None);

		MyGameMode->GenerateDungeon2(maxRoom, mapSize);

		//Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
		//FVector(0, 0, 64)
		FTimerDelegate timerdel;
		timerdel.BindUFunction(this, FName("MovementActive"));
		GetWorldTimerManager().SetTimer(timerHandle,timerdel, 1.0f, false, 0.0f);
		
	}
}

void AMyPawn::overlapDoor(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->Tags.Contains("Door")) {
		Other->SetActorLocation(FVector(0, 0, 10000));
	}
}

void AMyPawn::DeactiveInterAction() {
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}