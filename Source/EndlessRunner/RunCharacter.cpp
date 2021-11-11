// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunCharacterController.h"
// Sets default values
ARunCharacter::ARunCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 500.0f;
	springArm->bUsePawnControlRotation = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
	camera->bUsePawnControlRotation = true;


}

void ARunCharacter::Die()
{
	if (isAlive == true)
	{
		isAlive = false;
		GetMesh()->SetVisibility(false);
		if (ARunCharacterController* controller = Cast<ARunCharacterController>(UGameplayStatics::GetPlayerController(this, 0)))
		{
			
			controller->Disable();
		}


		onDeath.Broadcast();
	}

	
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	isAlive = true;
	
	
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunCharacter::AddCoin(int32 p_coinAmt)
{
	coin+= p_coinAmt;
}






