#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBoxActor.generated.h"

UCLASS()
class WECHATPLANE_API AEnemyBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBoxActor();
	//初始化位置
	void InitLocation();
	//对外的开关生成函数
	void StartSpawn();
	void StopSpawn();

protected:
	virtual void BeginPlay() override;
	//开关生成的bool
	bool bCanSpawn;
	//生成敌人的函数
	void SpawnEnemy(float DeltaTime);
	//生成敌人的定时器
	float SpawnTickTime;
	//生成间隔
	float SpawnInterval;
	//生成位置
	FVector SpawnLocation;
	float PosX;
public:	
	virtual void Tick(float DeltaTime) override;

};
