// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RunGameMode.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Pickup.h"
#include "RunCharacter.h"
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(sceneComponent);
	
	arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	arrowComponent->SetupAttachment(RootComponent);
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetupAttachment(RootComponent);
	obstacleSpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Spawn Box Component"));
	obstacleSpawnBounds->SetupAttachment(RootComponent);
	pickUpSpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Pick Up Spawn Box Component"));
	pickUpSpawnBounds->SetupAttachment(RootComponent);
	


}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentEndOverlap.AddDynamic(this, &ATile::OnOverlapEnd);
	
	
	SpawnObstacles();
	SpawnPickups();
	


	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SpawnObstacles()
{
	obstacleMaxAmount = FMath::RandRange(0, 3);
	for (int32 currentObstacleInstanceIndex = 0; currentObstacleInstanceIndex < obstacleMaxAmount; currentObstacleInstanceIndex++)
	{
		if (obstacleMaxAmount > 0) // If can spawn more than 1 instances of an object
		{
		
			if (obstacleTypes.Num() > 0) //If there are object classes
			{
				//Randomizing between different Obstacle types(use TArray<TSubclassOf<T>>)
				int32 chosenObstacleClassIndex = FMath::RandRange(0, obstacleTypes.Num()-1);
				FVector instanceLocation = UKismetMathLibrary::RandomPointInBoundingBox(obstacleSpawnBounds->Bounds.Origin, obstacleSpawnBounds->Bounds.BoxExtent);
				FActorSpawnParameters spawnParams;
				spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				spawnParams.bNoFail = true;


				FTransform instanceTransform;
				
				instanceTransform.SetLocation(instanceLocation);
			
				AObstacle* obstacleInstance = GetWorld()->SpawnActor<AObstacle>(obstacleTypes[chosenObstacleClassIndex], instanceTransform, spawnParams);
				obstacleInstances.Add(obstacleInstance);
		
			}
		}
	

	}


}

void ATile::SpawnPickups()
{
	pickUpMaxAmount = FMath::RandRange(0, 3);
	for (int32 currentPickUpInstanceIndex = 0; currentPickUpInstanceIndex < pickUpMaxAmount; currentPickUpInstanceIndex++)
	{
		if (pickUpMaxAmount > 0) // If can spawn more than 1 instances of an object
		{

			if (pickUpTypes.Num() > 0) //If there are object classes
			{
				int32 chosenPickUpClassIndex = FMath::RandRange(0, pickUpTypes.Num() - 1);
				FVector instanceLocation = UKismetMathLibrary::RandomPointInBoundingBox(pickUpSpawnBounds->Bounds.Origin, obstacleSpawnBounds->Bounds.BoxExtent);
				FActorSpawnParameters spawnParams;
				spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				spawnParams.bNoFail = true;


				FTransform instanceTransform;

				instanceTransform.SetLocation(instanceLocation);

				APickup* pickUpInstance = GetWorld()->SpawnActor<APickup>(pickUpTypes[chosenPickUpClassIndex], instanceTransform, spawnParams);
				pickUpInstances.Add(pickUpInstance);

			}
		}


	}


}

void ATile::Despawn()
{
	//	Spawned obstacle must be manually destroyed after the Tile has been destroyed.
	while (obstacleInstances.Num() > 0)
	{
		AObstacle* currentlySelectedObstacleInstance = obstacleInstances[0];
		obstacleInstances.RemoveSingle(obstacleInstances[0]);
		currentlySelectedObstacleInstance->Destroy();

	}
	
	while (pickUpInstances.Num() > 0)
	{
		APickup* currentlySelectedPickUpInstance = pickUpInstances[0];
		pickUpInstances.RemoveSingle(pickUpInstances[0]);
		currentlySelectedPickUpInstance->Destroy();

	}
	Destroy();

}


void ATile::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARunCharacter>(OtherActor))
	{
		//broadcast
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TEST");
		if (ARunGameMode* currentGameMode = Cast<ARunGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			onExited.Broadcast(this); //Calling delegate function
		
		}
	}


}

FTransform ATile::GetAttachTransform()
{
	
	return(arrowComponent->GetComponentTransform());

}

