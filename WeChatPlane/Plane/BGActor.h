#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGActor.generated.h"
class UStaticMeshComponent;
class UMaterial;
UCLASS()
class WECHATPLANE_API ABGActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABGActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* PlaneMeshComponent;
	UPROPERTY()
	UMaterial* PlaneMaterial;

public:	
	virtual void Tick(float DeltaTime) override;

};
