#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanePawn.generated.h"
class UPaperFlipbookComponent;
class UCameraComponent;
//两种子弹的枚举
UENUM(BlueprintType)
enum class EBulletType:uint8
{
	EDIT_SingleBullet UMETA(DisplayName="SingleBullet"),
	EDIT_DoubleBullet UMETA(DisplayName="DoubleBullet")
};
UCLASS()
class WECHATPLANE_API APlanePawn : public APawn
{
	GENERATED_BODY()

public:
	APlanePawn();
	//跟随鼠标
	void UpdatePlaneWithMouse(float DeltaTime);
	//发射子弹
	void Fire(float DeltaTime);
protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	UPaperFlipbookComponent* PlaneSpriteComponent;
	UPROPERTY()
	UCameraComponent* CameraComponent;
	FVector WordPos,WordDir;
	float TargetX,TargetZ;
	UPROPERTY()
	APlayerController* PController;
	//发射间隔
	float FireInterval;
	float FireTick;
	//发射位置
	UPROPERTY(EditAnywhere,Category="Plane")
	float FirePosition;
	//飞机的碰撞堆叠事件
	UFUNCTION()
	void OnPlaneOverlapBeginEvent(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	//当前的子弹类型
	EBulletType CurrentBulletType;
	//重置子弹类型的函数
	void ResetBulletType();
	//double bullet的定时器
	FTimerHandle DoubleBulletTimerHandle;
	//血量
	int32 HP;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
