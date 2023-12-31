#include "WeChatPlaneGameModeBase.h"

#include "BGActor.h"
#include "DropItemActor.h"
#include "EnemyBoxActor.h"
#include "PlanePawn.h"

AWeChatPlaneGameModeBase::AWeChatPlaneGameModeBase()
{
	DefaultPawnClass = APlanePawn::StaticClass();
}

void AWeChatPlaneGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//创建背景
	BgActor = GetWorld()->SpawnActor<ABGActor>(ABGActor::StaticClass(),FVector(0,-10,0),FRotator(0,0,90));
	//创建掉落物
	GetWorld()->SpawnActor<ADropItemActor>(ADropItemActor::StaticClass(),FVector(0,0,400),FRotator(0,0,0))->SetDropItemType(EDropItemType::EDIT_DoubleBullet);
	//创建怪物的生成点
	EnemyBoxActor = GetWorld()->SpawnActor<AEnemyBoxActor>();
	//延迟一秒初始化位置
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AWeChatPlaneGameModeBase::DelayInitLocation,0.5f);
	
}

void AWeChatPlaneGameModeBase::DelayInitLocation() const
{
	EnemyBoxActor->InitLocation();
}
