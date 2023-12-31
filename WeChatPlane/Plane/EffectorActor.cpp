#include "EffectorActor.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

AEffectorActor::AEffectorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//创建精灵组件
	EffectorFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EffectorSpriteComponent"));
	EffectorFlipbookComponent->SetupAttachment(RootComponent);
	//设置位置
	EffectorFlipbookComponent->SetRelativeLocation(FVector(0.0f,1.0f,0.0f));
}

void AEffectorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffectorActor::PlayEffectCallBack()
{
	//摧毁自身
	Destroy();
}

void AEffectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEffectorActor::PlayEffect(const TCHAR* Path, bool bLoop)
{
	EffectorFlipbook = LoadObject<UPaperFlipbook>(nullptr,Path);
	if (!EffectorFlipbook)
	{
		return -1;
	}
	EffectorFlipbookComponent->SetFlipbook(EffectorFlipbook);
	if (!bLoop)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle,this,&AEffectorActor::PlayEffectCallBack,EffectorFlipbook->GetTotalDuration(),false);
	}
	return EffectorFlipbook->GetTotalDuration();
}

