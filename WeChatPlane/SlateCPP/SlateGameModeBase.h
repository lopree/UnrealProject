#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlateGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WECHATPLANE_API ASlateGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	ASlateGameModeBase();
	UFUNCTION(Exec)
	void RegisterTable();
	UFUNCTION(Exec)
	void ShowTableUI();
	UFUNCTION(Exec)
	void ReleaseTable();
	FName TableID;
	TSharedRef<class SDockTab> SpawnTabUI(const class FSpawnTabArgs& Args);
	//加载UMG
	TSharedRef<class SDockTab> SpawnUMGUI(const class FSpawnTabArgs& Args);
	bool bLoadUMG = true;
	//-----------------Json-----------------
	UFUNCTION(Exec)
	void ParseJson();
	UFUNCTION(Exec)
	void WriteJson();
	UFUNCTION(Exec)
	void WriteAllActorToJson();
	UFUNCTION(Exec)
	void ReadXML();
	UFUNCTION(Exec)
	void UpdateXmlData();
};
