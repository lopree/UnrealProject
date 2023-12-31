#include "PlaneBulletActor.h"

#include "EnemyActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

APlaneBulletActor::APlaneBulletActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建根组件
	BulletSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BulletSpriteComponent"));
	SetRootComponent(BulletSpriteComponent);
	//加载子弹精灵
	static ConstructorHelpers::FObjectFinder<UPaperSprite> BulletSpriteObj(TEXT("/Script/Paper2D.PaperSprite'/Game/Texture/Bullet/Bullet01_Sprite.Bullet01_Sprite'"));
	//设置子弹精灵
	BulletSpriteComponent->SetSprite(BulletSpriteObj.Object);

	FlySpeed = 450.0f;
	//开启碰撞
	BulletSpriteComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//设置碰撞类型
	BulletSpriteComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//设置碰撞响应
	BulletSpriteComponent->OnComponentBeginOverlap.AddDynamic(this,&APlaneBulletActor::OnBulletOverlapBeginEvent);
}

void APlaneBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlaneBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Fly(DeltaTime);
}

void APlaneBulletActor::Fly(float DeltaTime)
{
	AddActorWorldOffset(FVector::UpVector*DeltaTime*FlySpeed);
}

void APlaneBulletActor::OnBulletOverlapBeginEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyActor* EnemyActor = Cast<AEnemyActor>(OtherActor))
	{
		//销毁敌人
		EnemyActor->Hurt();
		//销毁子弹
		Destroy();
	}
}

