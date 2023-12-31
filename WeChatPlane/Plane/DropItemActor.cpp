#include "DropItemActor.h"
#include <PaperSprite.h>
#include <PaperSpriteComponent.h>
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

ADropItemActor::ADropItemActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//路径赋值
	DropItemSpritePath_DoubleBullet = TEXT("/Script/Paper2D.PaperSprite'/Game/Texture/DropItem/DoubleBullet_Sprite.DoubleBullet_Sprite'");
	DropItemSpritePath_Bomb = TEXT("/Script/Paper2D.PaperSprite'/Game/Texture/DropItem/Boom_Sprite.Boom_Sprite'");
}

void ADropItemActor::SetDropItemType(EDropItemType NewDropItemType)
{
	FString ItemSourcePath;
	if (NewDropItemType == EDropItemType::EDIT_DoubleBullet)
	{
		ItemSourcePath = DropItemSpritePath_DoubleBullet;
	}else
	{
		ItemSourcePath = DropItemSpritePath_Bomb;
	}
	//加载精灵
	UPaperSprite* DropItemSprite = LoadObject<UPaperSprite>(nullptr,*ItemSourcePath);
	//设置精灵
	DropSpriteRenderComponent->SetSprite(DropItemSprite);
	DropItemType = NewDropItemType;
}

void ADropItemActor::BombAllEnemy()
{
	TArray<AActor*> AllEnemyActors;
	UGameplayStatics::GetAllActorsOfClass(this,AEnemyActor::StaticClass(),AllEnemyActors);
	//循环遍历所有敌人，调用他们自身的死亡函数
	for (AActor* EnemyActor:AllEnemyActors)
	{
		if (AEnemyActor* Enemy = Cast<AEnemyActor>(EnemyActor))
		{
			Enemy->Dead();
		}
	}
	//摧毁自己
	Destroy();
}

void ADropItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

