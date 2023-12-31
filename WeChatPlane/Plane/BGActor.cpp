#include "BGActor.h"

ABGActor::ABGActor()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//创建飞机精灵组件
	PlaneMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMeshComponent"));
	
	//加载Plane的资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	PlaneMeshComponent->SetStaticMesh(PlaneMeshObj.Object);
	//将材质球挂载到飞机精灵组件上
	static ConstructorHelpers::FObjectFinder<UMaterial> PlaneMaterialObj(TEXT("/Script/Engine.Material'/Game/Materials/M_BG.M_BG'"));
	PlaneMeshComponent->SetMaterial(0,PlaneMaterialObj.Object);
	//作为根组件
	SetRootComponent(PlaneMeshComponent);
	PlaneMeshComponent->SetRelativeScale3D(FVector(10,17,1));
	
	

}

void ABGActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABGActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

