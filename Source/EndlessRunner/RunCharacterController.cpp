// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacterController.h"
#include "RunCharacter.h"
#include "GameFramework/Controller.h"

//Sets default values
ARunCharacterController::ARunCharacterController()
{
	
}

void ARunCharacterController::BeginPlay()
{
	Super::BeginPlay();
	runCharacter = Cast<ARunCharacter>(GetCharacter());

}

void ARunCharacterController::MoveForward()
{
	runCharacter->AddMovementInput(runCharacter->GetActorForwardVector(), 1);
}

void ARunCharacterController::MoveRight(float p_scale)
{
	
	runCharacter->AddMovementInput(runCharacter->GetActorRightVector() * p_scale);
}



// Called every frame
void ARunCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (runCharacter != NULL)
	{
		if (runCharacter->isAlive)
		{

			MoveForward();
		}
	}
}


void ARunCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &ARunCharacterController::MoveRight);

}

void ARunCharacterController::Enable()
{
	EnableInput(Cast<ARunCharacterController>(this));
}

void ARunCharacterController::Disable()
{
	DisableInput(Cast<ARunCharacterController>(this));

}


