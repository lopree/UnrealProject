#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectorActor.generated.h"

UCLASS()
class WECHATPLANE_API AEffectorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectorActor();
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	class UPaperFlipbookComponent* EffectorFlipbookComponent;
	UPROPERTY()
	class UPaperFlipbook* EffectorFlipbook;
	void PlayEffectCallBack();
public:	
	virtual void Tick(float DeltaTime) override;
	float PlayEffect(const TCHAR* Path,bool bLoop = false);
};
