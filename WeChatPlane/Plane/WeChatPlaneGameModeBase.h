#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WeChatPlaneGameModeBase.generated.h"

UCLASS()
class WECHATPLANE_API AWeChatPlaneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWeChatPlaneGameModeBase();
protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	class ABGActor* BgActor;
	UPROPERTY()
	class AEnemyBoxActor* EnemyBoxActor;
	//初始化位置
	void DelayInitLocation() const;
};
