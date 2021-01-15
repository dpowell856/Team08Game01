// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TwoTheEdgeCharacter.generated.h"

UCLASS(config=Game)
class ATwoTheEdgeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Extra movement options */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UExtraMovementComponent* ExtraMovement;
	
public:
	ATwoTheEdgeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* PlayerNameClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture*> PlayerColourTextures;

protected:

	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual void Jump() override;

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Called to crouch */
	void DoCrouch();
	void DoUnCrouch();

	/** Called to sprint */
	void Sprint();
	void Walk();
	UFUNCTION(BlueprintImplementableEvent)
	void OnSprint(bool IsSprinting);

	/** Called to forward dash */
	void ForwardDash();
	UFUNCTION(BlueprintImplementableEvent)
	void OnForwardDash();

	/** Creates the names over the players' heads */
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void CreatePlayerName(APlayerCameraManager* CameraManager);

	UFUNCTION(BlueprintCallable)
	void Respawn();
	UFUNCTION(Server, Reliable)
	void RespawnOnServer();
	UFUNCTION(Client, Reliable)
	void RespawnOnClient();
	UFUNCTION(NetMulticast, Reliable)
    void RespawnOnHost();
	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawn();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void TeleportOnServer(const FVector& DestLocation, const FRotator& DestRotation);

	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void OnPossessed(AController* NewController);
	UFUNCTION(BlueprintImplementableEvent)
	void PossessedServer(AController* NewController);

	UFUNCTION(BlueprintCallable)
	void RequestGrenadeThrow(const int32& GrenadeType);
	UFUNCTION(Server, Reliable)
	void GrenadeThrowServer(const int32& GrenadeType);
	UFUNCTION(Client, Reliable)
	void GrenadeThrowClient(const int32& GrenadeType);
	UFUNCTION(NetMulticast, Reliable)
    void GrenadeThrowNetCast(const int32& GrenadeType);
	UFUNCTION(BlueprintImplementableEvent)
	void OnGrenadeThrow(const int32& GrenadeType);

	UFUNCTION(BlueprintImplementableEvent)
	void OnJump();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentJumpCount() const { return JumpCurrentCount; }
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

