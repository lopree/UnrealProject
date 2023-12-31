#pragma once

#include "CoreMinimal.h"
#include "DropSceneActor.h"
#include "PaperSpriteActor.h"
#include "EnemyActor.generated.h"

UCLASS()
class WECHATPLANE_API AEnemyActor : public ADropSceneActor
{
	GENERATED_BODY()
public:
	void Dead();
	void Hurt();
protected:
	virtual void BeginPlay() override;
	int32 HP;
	void TurnToDead();
	void TurnToHurt();
};
