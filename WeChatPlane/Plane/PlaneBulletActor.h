#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaneBulletActor.generated.h"
class UPaperSpriteComponent;
UCLASS()
class WECHATPLANE_API APlaneBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlaneBulletActor();

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	UPaperSpriteComponent* BulletSpriteComponent;
	//飞行
	void Fly(float DeltaTime);
	//飞行速度
	UPROPERTY(EditAnywhere,Category="PlaneBullet")
	float FlySpeed;
	//碰撞堆叠事件
	UFUNCTION()
	void OnBulletOverlapBeginEvent(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

};
