// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class ENDLESSRUNNER_API ARunCharacter : public ACharacter
{
	GENERATED_BODY() 

public:
	// Sets default values for this character's properties
	ARunCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool isAlive;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
		FOnDeath onDeath;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void AddCoin(int32 p_coinAmt);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
		int32 coin;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Die();



};
