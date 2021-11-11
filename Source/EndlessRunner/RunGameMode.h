// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"


/**
 * 
 */


UCLASS()
class ENDLESSRUNNER_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARunGameMode();


	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "BeginPlayBlueprint"))
		void BeginPlayBlueprint();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void AddTile();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void DespawnTile(class ATile* p_tile);

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void OnTileAdded(ATile* tile);

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void EndLevel();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void RestartLevel();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		class TSubclassOf<class ATile>tileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		FTransform NextTileTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 maxTileRenderedCount;
};
