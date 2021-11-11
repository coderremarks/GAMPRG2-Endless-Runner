// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "Tile.h"
#include "Engine/World.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
ARunGameMode::ARunGameMode()
{

}

// Called when the game starts or when spawned
void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Spawning initial tiles
	for (int32 currentTileIndex = 0; currentTileIndex < maxTileRenderedCount; currentTileIndex++)
	{
		AddTile();
	}
	BeginPlayBlueprint();

}

void ARunGameMode::EndLevel()
{
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARunGameMode::RestartLevel, 2, false);
}

void ARunGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ARunGameMode::AddTile()
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.bNoFail = true;


	FTransform transform;
	transform = NextTileTransform;

	ATile* tileInstance = GetWorld()->SpawnActor<ATile>(tileClass, transform, spawnParams);


	if (tileInstance)
	{
		tileInstance->onExited.AddDynamic(this, &ARunGameMode::OnTileAdded);
		
		NextTileTransform = tileInstance->GetAttachTransform();
	}
	
	
		

	
}

void ARunGameMode::OnTileAdded(class ATile* tile)
{
	AddTile();
	FTimerHandle timerHandle;
	FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &ARunGameMode::DespawnTile, tile);
	GetWorldTimerManager().SetTimer(timerHandle, timerDelegate, 0.5f, false);
}

void ARunGameMode::DespawnTile(class ATile* p_tile)
{
	p_tile->Despawn();

}

