// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExited, class ATile*, tileToBeDeleted);

UCLASS()
class ENDLESSRUNNER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
		FOnExited onExited;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		FTransform GetAttachTransform();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Despawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* sceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* arrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* boxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* obstacleSpawnBounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* pickUpSpawnBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray <class TSubclassOf<class AObstacle>> obstacleTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray<class AObstacle*> obstacleInstances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 obstacleMaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray <class TSubclassOf<class APickup>> pickUpTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray<class APickup*> pickUpInstances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 pickUpMaxAmount;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void SpawnObstacles();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void SpawnPickups();




};
