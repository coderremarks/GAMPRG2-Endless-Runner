// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ARunCharacterController(); 

	//Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Enable();
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Disable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
		class ARunCharacter* runCharacter;


private:
	// Called to bind functionality to input
	UFUNCTION()
		virtual void SetupInputComponent() override;

	UFUNCTION()
		void MoveForward();

	UFUNCTION()
		void MoveRight(float p_scale);



};


