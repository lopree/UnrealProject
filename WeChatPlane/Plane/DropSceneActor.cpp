#include "DropSceneActor.h"

#include "PaperSpriteComponent.h"

ADropSceneActor::ADropSceneActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建组件
	DropSpriteRenderComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DropSpriteRenderComponent"));
	//设置根组件
	SetRootComponent(DropSpriteRenderComponent);
	//初始化数据
	DropSpeed = 100.f;
}

void ADropSceneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropSceneActor::Drop(float DeltaTime)
{
	if (DropSpeed == 0.f)
	{
		return;
	}
	AddActorWorldOffset(FVector::UpVector * -1 * DropSpeed * DeltaTime);
}

void ADropSceneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Drop(DeltaTime);
}

