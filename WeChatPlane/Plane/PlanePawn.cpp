#include "PlanePawn.h"

#include "DropItemActor.h"
#include "EffectorActor.h"
#include "EnemyActor.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PlaneBulletActor.h"

APlanePawn::APlanePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//创建飞机精灵组件
	PlaneSpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlaneSpriteComponent"));
	//设置飞机的碰撞堆叠
	PlaneSpriteComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//设置飞机的碰撞响应
	PlaneSpriteComponent->OnComponentBeginOverlap.AddDynamic(this,&APlanePawn::OnPlaneOverlapBeginEvent);
	//将飞机精灵组件挂载到根组件上
	PlaneSpriteComponent->SetupAttachment(RootComponent);
	//创建摄像机组件
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//将摄像机组件挂载到根组件上
	CameraComponent->SetupAttachment(RootComponent);
	//设置摄像机的旋转
	CameraComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	//设置摄像机的位置
	CameraComponent->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	//设置摄像机的投影模式
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	//设置摄像机的正交宽度
	CameraComponent->OrthoWidth =2500.0f;
	//加载飞机精灵
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PlaneFlipbookObj(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Texture/Plane/FB_Plane.FB_Plane'"));
	if (PlaneFlipbookObj.Succeeded())
	{
		PlaneSpriteComponent->SetFlipbook(PlaneFlipbookObj.Object);
	}else
	{
		UE_LOG(LogTemp,Log,TEXT("加载飞机精灵失败"));
	}
	//初始化数据
	FireTick = 0.5f;
	FireInterval = 0.5f;
	FirePosition = 80.0f;
	CurrentBulletType = EBulletType::EDIT_SingleBullet;
	HP = 3;
}

void APlanePawn::UpdatePlaneWithMouse(float DeltaTime)
{
	PController->DeprojectMousePositionToWorld(WordPos,WordDir);
	TargetX = FMath::FInterpTo(PlaneSpriteComponent->GetComponentLocation().X,WordPos.X,DeltaTime,5.0f);
	TargetZ = FMath::FInterpTo(PlaneSpriteComponent->GetComponentLocation().Z,WordPos.Z,DeltaTime,5.0f);
	PlaneSpriteComponent->SetWorldLocation(FVector(TargetX,0.0f,TargetZ));
}

void APlanePawn::Fire(float DeltaTime)
{
	if ((FireTick -= DeltaTime) < 0.0f)
	{
		if (CurrentBulletType == EBulletType::EDIT_SingleBullet)
		{
			GetWorld()->SpawnActor<APlaneBulletActor>(PlaneSpriteComponent->GetComponentLocation() + FVector::UpVector * FirePosition,FRotator::ZeroRotator);
		}else
		{
			GetWorld()->SpawnActor<APlaneBulletActor>(PlaneSpriteComponent->GetComponentLocation() + FVector::UpVector * FirePosition + FVector::ForwardVector * 30,FRotator::ZeroRotator);
			GetWorld()->SpawnActor<APlaneBulletActor>(PlaneSpriteComponent->GetComponentLocation() + FVector::UpVector * FirePosition - FVector::ForwardVector * 30,FRotator::ZeroRotator);
		}
		FireTick =FireInterval;
	}
}

void APlanePawn::BeginPlay()
{
	Super::BeginPlay();
	//不要在构造函数中获取控制器，因为控制器在构造函数中还没有创建（世界还没初始化完成）
	PController = Cast<APlayerController>(GetController());
	PController->bShowMouseCursor= true;
}

void APlanePawn::OnPlaneOverlapBeginEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADropItemActor* DropItemActor = Cast<ADropItemActor>(OtherActor))
	{
		if (DropItemActor->GetDropItemType() == EDropItemType::EDIT_DoubleBullet)
		{
			//重置定时器
			if (CurrentBulletType == EBulletType::EDIT_DoubleBullet)
			{
				GetWorldTimerManager().ClearTimer(DoubleBulletTimerHandle);
			}
			GetWorldTimerManager().SetTimer(DoubleBulletTimerHandle,this,&APlanePawn::ResetBulletType,5.0f,false);
			CurrentBulletType = EBulletType::EDIT_DoubleBullet;
			DropItemActor->Destroy();
		}else
		{
			DropItemActor->BombAllEnemy();
		}
	}else if(AEnemyActor* EnemyActor = Cast<AEnemyActor>(OtherActor))
	{
		EnemyActor->Hurt();
		//添加爆炸
		AEffectorActor* EffectorActor = GetWorld()->SpawnActor<AEffectorActor>(PlaneSpriteComponent->GetComponentLocation(),FRotator::ZeroRotator);
		EffectorActor->PlayEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Texture/Plane/FB_PlaneBoom.FB_PlaneBoom'"));
	}
			
}

void APlanePawn::ResetBulletType()
{
	CurrentBulletType = EBulletType::EDIT_SingleBullet;
}

void APlanePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePlaneWithMouse(DeltaTime);
	Fire(DeltaTime);
}

void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

