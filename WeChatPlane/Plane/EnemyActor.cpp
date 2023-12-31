#include "EnemyActor.h"

#include "EffectorActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

void AEnemyActor::Dead()
{
	TurnToDead();
}

void AEnemyActor::Hurt()
{
	--HP;
	if (HP <= 0)
	{
		TurnToDead();
	}
}

void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	UPaperSprite* EnemySprite = LoadObject<UPaperSprite>(nullptr,TEXT("/Script/Paper2D.PaperSprite'/Game/Texture/Enemy/Enemy01_Sprite.Enemy01_Sprite'"));
	DropSpriteRenderComponent->SetSprite(EnemySprite);
}

void AEnemyActor::TurnToDead()
{
	Destroy();
	//播放爆炸特效
	AEffectorActor* EffectorActor = GetWorld()->SpawnActor<AEffectorActor>(DropSpriteRenderComponent->GetComponentLocation(),FRotator::ZeroRotator);
	EffectorActor->PlayEffect(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Texture/Enemy/FB_EnemyBoom.FB_EnemyBoom'"));
}

void AEnemyActor::TurnToHurt()
{
	
}
