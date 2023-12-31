#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropSceneActor.generated.h"
class UPaperSpriteComponent;
UCLASS()
class WECHATPLANE_API ADropSceneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADropSceneActor();

protected:
	virtual void BeginPlay() override;
	//Sprite组件
	UPROPERTY()
	UPaperSpriteComponent* DropSpriteRenderComponent;
	//掉落速度
	float DropSpeed;
	//掉落方式函数
	void Drop(float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;

};
