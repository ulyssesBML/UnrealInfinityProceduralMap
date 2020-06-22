// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ground.generated.h"

UCLASS()
class MYPROJECT_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGround();
	UStaticMesh* FloorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UInstancedStaticMeshComponent* ISMesh;
	UPROPERTY(EditAnywhere)
	AActor* Player;
	UPROPERTY(EditAnywhere)
	FVector square_max;
	UPROPERTY(EditAnywhere)
	FVector square_min;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
