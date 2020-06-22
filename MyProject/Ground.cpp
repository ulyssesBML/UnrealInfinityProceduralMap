// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> floorMesh_obj(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	FloorMesh = floorMesh_obj.Object;

	ISMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMesh"));
}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(GetTransform()));
	for(int x=-10; x<10;x++){
		for(int y=-10; y<10;y++){
			FTransform transf = FTransform(FRotator(0,0,0),FVector(x*200,y*200,0),FVector(200,200,1));
			ISMesh->AddInstance(transf);
		}
	}


}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FBox box = FBox(Player->GetTransform().GetLocation()+FVector(750,250,0),Player->GetTransform().GetLocation()+FVector(850,350,-100));

	for(int i=-30;i<30;i++){
		for(int j=0;j<3;j++){
			FBox box = FBox(FVector(0,0,0),FVector(0,0,0));
			FTransform MyTransform = FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(1,1,1));

			if(j==0){
				box = FBox(
						(((Player->GetTransform().GetLocation() * FVector(1,1,0))+square_min ) + FVector(0,i*(square_max.Y - square_min.Y),0)),
						(((Player->GetTransform().GetLocation() * FVector(1,1,0))+square_max) + FVector(0,i*(square_max.Y - square_min.Y),0))
					);
				DrawDebugSolidBox(GetWorld(), box, FColor(20, 100, 240,100), MyTransform, false);
				
			}
			if(j==1){
				box = FBox(
						(((Player->GetTransform().GetLocation() * FVector(1,1,0))+(square_min * FVector(-1,1,1)) ) + FVector(0,i*(square_max.Y - square_min.Y),0)),
						(((Player->GetTransform().GetLocation() * FVector(1,1,0))+(square_max* FVector(-1,1,1)))  + FVector(0,i*(square_max.Y - square_min.Y),0))
					);
				DrawDebugSolidBox(GetWorld(), box, FColor(240, 100, 20,100), MyTransform, false);
				
			}
			if(j==2){
				box = FBox(
					(((Player->GetTransform().GetLocation() * FVector(1,1,0))+square_min ) + FVector(i*(square_max.Y - square_min.Y),0+10000,0)),
					(((Player->GetTransform().GetLocation() * FVector(1,1,0))+square_max) + FVector(i*(square_max.Y - square_min.Y),0+10000,0))
				);
				
				DrawDebugSolidBox(GetWorld(), box, FColor(240, 240, 100,100), MyTransform, false);
			}
			else{
				
			}
			
			TArray <int32> aux_a = ISMesh->GetInstancesOverlappingBox(box,true);

			if(aux_a.Num() <= 0){
				ISMesh->AddInstanceWorldSpace(FTransform(FRotator(0,0,0),(box.Min+box.Max)/2,FVector(20,20,1)));
			}
		}
		
	}

	//DrawDebugBox(GetWorld(), Player->GetTransform().GetLocation()+FVector(1000,0,0),FVector(100,100,100), FColor::Purple, false, -1, 0, 10);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), aux_a.Num()));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("cont: %d"), ISMesh->GetInstanceCount()));

	//if(aux_a.Num() <= 0){
	//	ISMesh->AddInstanceWorldSpace(FTransform(FRotator(0,0,0),box.Max,FVector(1,1,1)));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("X: %d Y: %d Z: %d"),Player->GetTransform().GetLocation().X,Player->GetTransform().GetLocation().Y,Player->GetTransform().GetLocation().Z));


}

