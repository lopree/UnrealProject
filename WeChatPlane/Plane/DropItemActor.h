#pragma once

#include "CoreMinimal.h"
#include "DropSceneActor.h"
#include "DropItemActor.generated.h"
//两种凋落物的枚举
UENUM(BlueprintType)
enum class EDropItemType:uint8
{
	EDIT_DoubleBullet UMETA(DisplayName="DoubleBullet"),
	EDIT_Bomb UMETA(DisplayName="Bomb")
};
UCLASS()
class WECHATPLANE_API ADropItemActor : public ADropSceneActor
{
	GENERATED_BODY()
	
public:	
	ADropItemActor();
	//更改凋落物
	void SetDropItemType(EDropItemType NewDropItemType);
	EDropItemType GetDropItemType() const {return DropItemType;}
	//炸弹类型的掉落包，炸死所有敌人
	void BombAllEnemy();
protected:
	virtual void BeginPlay() override;
	//凋落物类型
	EDropItemType DropItemType;
	//第一个凋落物的精灵文件路径
	FString DropItemSpritePath_DoubleBullet;
	//第二个凋落物的精灵文件路径
	FString DropItemSpritePath_Bomb;

public:	
	virtual void Tick(float DeltaTime) override;

};
