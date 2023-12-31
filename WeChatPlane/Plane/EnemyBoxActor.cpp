#include "EnemyBoxActor.h"

#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

AEnemyBoxActor::AEnemyBoxActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AEnemyBoxActor::InitLocation()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this,0))
	{
		int32 SizeX, SizeY;
		PC->GetViewportSize(SizeX, SizeY);
		FVector WorldLocation;
		FVector WorldDirection;
		PC->DeprojectScreenPositionToWorld(SizeX / 2, 0, WorldLocation, WorldDirection);
		SetActorLocation(WorldLocation + FVector::UpVector * 50);
		StartSpawn();
	}
}

void AEnemyBoxActor::StartSpawn()
{
	bCanSpawn = true;
}
void AEnemyBoxActor::StopSpawn()
{
	bCanSpawn = false;
}

void AEnemyBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBoxActor::SpawnEnemy(float DeltaTime)
{
	if (!bCanSpawn)
	{
		return;
	}
	if ((SpawnTickTime += DeltaTime) >= SpawnInterval)
	{
		//生成敌人
		SpawnLocation = GetActorLocation();
		//X轴为此位置的+-200
		PosX = FMath::RandRange(SpawnLocation.X-200.f,SpawnLocation.X+200.f);
		GetWorld()->SpawnActor<AEnemyActor>(AEnemyActor::StaticClass(),FVector(PosX,0,SpawnLocation.Z),FRotator::ZeroRotator);
		//重置
		SpawnTickTime = 0.f;
		SpawnInterval = FMath::RandRange(0.5f,1.5f);
	}
	
}

void AEnemyBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnEnemy(DeltaTime);

}

