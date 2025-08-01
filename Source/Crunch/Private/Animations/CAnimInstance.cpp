// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>



void UCAnimInstance::NativeInitializeAnimation()
{
	OwnerPlayerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerPlayerCharacter)
	{
		OwnerMovementComp = OwnerPlayerCharacter->GetCharacterMovement();
	}
	else
	{
		OwnerMovementComp = nullptr;
	}
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerPlayerCharacter)
	{
		Speed = OwnerPlayerCharacter->GetVelocity().Length();
		FRotator BodyRot = OwnerPlayerCharacter->GetActorRotation();
		FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
		BodyPrevRot = BodyRot;

		YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmothLerpSpeed);
	}
}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

}
