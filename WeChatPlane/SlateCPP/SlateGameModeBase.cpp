#include "SlateGameModeBase.h"

#include "XmlFile.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASlateGameModeBase::ASlateGameModeBase()
{
	TableID = FName(TEXT("MyTabUI"));
}

void ASlateGameModeBase::RegisterTable()
{
	if (bLoadUMG)
	{
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TableID, FOnSpawnTab::CreateUObject(this,&ASlateGameModeBase::SpawnUMGUI))
			.SetDisplayName(FText::FromString(TEXT("CustomSlateTableDisplayName")));
	}else
	{
		//注册table代理
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TableID, FOnSpawnTab::CreateUObject(this,&ASlateGameModeBase::SpawnTabUI))
			.SetDisplayName(FText::FromString(TEXT("CustomSlateTableDisplayName")));
	}
}

void ASlateGameModeBase::ShowTableUI()
{
	//显示table
	FGlobalTabmanager::Get()->TryInvokeTab(TableID);
}

void ASlateGameModeBase::ReleaseTable()
{
	//注销table
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TableID);
}

TSharedRef<SDockTab> ASlateGameModeBase::SpawnTabUI(const class FSpawnTabArgs& Args)
{
	return SNew(SDockTab).TabRole(NomadTab)
		[
			//插入垂直分布
			SNew(SVerticalBox)
			+SVerticalBox::Slot().FillHeight(50)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("账号：")))
				]
				+SHorizontalBox::Slot().HAlign(HAlign_Center)
				[
					SNew(SEditableTextBox).Text(FText::FromString(TEXT("请输入账号")))
				]
			]
			+SVerticalBox::Slot().FillHeight(50)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("密码：")))
				]
				+SHorizontalBox::Slot().HAlign(HAlign_Center)
				[
					SNew(SEditableTextBox).Text(FText::FromString(TEXT("请输入密码")))
				]
			]
			+SVerticalBox::Slot().FillHeight(50)
			[
				SNew(SButton).HAlign(HAlign_Center).VAlign(VAlign_Center).OnClicked(FOnClicked::CreateLambda([]()->FReply
				{
					UE_LOG(LogTemp,Log,TEXT("点击了"));
					return FReply::Handled();
				}))
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("登录")))
				]
			]
		];
}

TSharedRef<SDockTab> ASlateGameModeBase::SpawnUMGUI(const FSpawnTabArgs& Args)
{
	TSubclassOf<UUserWidget> CustomUMG = LoadClass<UUserWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Slate/UMG_Test/UMG_Test.UMG_Test_C'"));
	UUserWidget* CustomUMGWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(),CustomUMG);
	return SNew(SDockTab).TabRole(NomadTab)
		[
			CustomUMGWidget->TakeWidget()
		];
}

void ASlateGameModeBase::ParseJson()
{
	//读取Json文件
	FString JSFile;
	if (FFileHelper::LoadFileToString(JSFile,TEXT("D:\\Download\\Person.json")))
	{
		//打印是否读取成功
		//UE_LOG(LogTemp,Log,TEXT("读取成功%s"),*JSFile);
		//解析Json
		TSharedPtr<FJsonObject> RootJsonObj;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JSFile);
		if (FJsonSerializer::Deserialize(JsonReader,RootJsonObj))
		{
			if (RootJsonObj->HasTypedField<EJson::Array>("Characters"))
			{
				TArray<TSharedPtr<FJsonValue>> CharactersArray = RootJsonObj->GetArrayField("Characters");
				if (CharactersArray.Num() > 0 && CharactersArray[0]->AsObject()->HasTypedField<EJson::Array>("Teachers"))
				{
					TArray<TSharedPtr<FJsonValue>> TeachersArray = CharactersArray[0]->AsObject()->GetArrayField("Teachers");
					if (TeachersArray.Num() > 0)
					{
						TSharedPtr<FJsonObject> FirstTeacher =TeachersArray[0]->AsObject()->GetObjectField("Zhao Liu");
						if (FirstTeacher->HasTypedField<EJson::Array>("Hobbies"))
						{
							TArray<TSharedPtr<FJsonValue>> HobbiesArray = FirstTeacher->GetArrayField("Hobbies");
							for (int32 i = 0; i < HobbiesArray.Num(); i++)
							{
								FString Hobby = HobbiesArray[i]->AsString();
								UE_LOG(LogTemp, Warning, TEXT("Hobby: %s"), *Hobby);
							}
						}else
						{
							//输出没有该属性
							UE_LOG(LogTemp,Warning,TEXT("没有该属性"));
						}
					}
				}
			}
		}
	}
}

void ASlateGameModeBase::WriteJson()
{
	//创建Json对象
	TSharedPtr<FJsonObject> RootJsonObj = MakeShareable(new FJsonObject);
	//设置一个简单的内容
	RootJsonObj->SetStringField("Name",TEXT("Zhang San"));
	RootJsonObj->SetNumberField("Age",18);
	RootJsonObj->SetBoolField("IsMarried",false);
	FString JsonStr;
	//序列化Json对象
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(RootJsonObj.ToSharedRef(),JsonWriter);
	//保存Json文件
	FFileHelper::SaveStringToFile(JsonStr,TEXT("D:\\Download\\Write.json"));
}

void ASlateGameModeBase::WriteAllActorToJson()
{
	//获得所有的Actor
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(),AllActors);
	//创建Json对象
	TSharedPtr<FJsonObject> RootJsonObj = MakeShareable(new FJsonObject);
	//循环所有的actor，填入信息
	for (int32 i = 0; i < AllActors.Num(); i++)
	{
		TSharedPtr<FJsonObject> ActorJsonObj = MakeShareable(new FJsonObject);
		ActorJsonObj->SetStringField("Name",AllActors[i]->GetName());
		{
			//location
			TSharedPtr<FJsonObject> LocationJsonObj = MakeShareable(new FJsonObject);
			LocationJsonObj->SetNumberField("X",AllActors[i]->GetActorLocation().X);
			LocationJsonObj->SetNumberField("Y",AllActors[i]->GetActorLocation().Y);
			LocationJsonObj->SetNumberField("Z",AllActors[i]->GetActorLocation().Z);
			ActorJsonObj->SetObjectField("Location",LocationJsonObj);
		}
		{
			//rotation
			TSharedPtr<FJsonObject> RotationJsonObj = MakeShareable(new FJsonObject);
			RotationJsonObj->SetNumberField("Pitch",AllActors[i]->GetActorRotation().Pitch);
			RotationJsonObj->SetNumberField("Yaw",AllActors[i]->GetActorRotation().Yaw);
			RotationJsonObj->SetNumberField("Roll",AllActors[i]->GetActorRotation().Roll);
			ActorJsonObj->SetObjectField("Rotation",RotationJsonObj);
		}
		{
			//scale
			TSharedPtr<FJsonObject> ScaleJsonObj = MakeShareable(new FJsonObject);
			ScaleJsonObj->SetNumberField("X",AllActors[i]->GetActorScale().X);
			ScaleJsonObj->SetNumberField("Y",AllActors[i]->GetActorScale().Y);
			ScaleJsonObj->SetNumberField("Z",AllActors[i]->GetActorScale().Z);
			ActorJsonObj->SetObjectField("Scale",ScaleJsonObj);
		}
		RootJsonObj->SetObjectField(FString::FromInt(i),ActorJsonObj);
	}
	//序列化Json对象
	FString JsonStr;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(RootJsonObj.ToSharedRef(),JsonWriter);
	//保存Json文件
	FFileHelper::SaveStringToFile(JsonStr,TEXT("D:\\Download\\WriteAllActorToJson.json"));
}

void ASlateGameModeBase::ReadXML()
{
	//读取XML文件
	FString XMLFile;
	TSharedPtr<FXmlFile> XMLFileReader = MakeShareable(new FXmlFile(TEXT("D:\\Download\\XMLExample.xml")));
	if (XMLFileReader.IsValid())
	{
		TArray<FXmlNode*> AllNodes = XMLFileReader->GetRootNode()->GetChildrenNodes();
		//打印数量
		UE_LOG(LogTemp,Warning,TEXT("数量：%d"),AllNodes.Num());
		TArray<FXmlNode*> PersonInfo = AllNodes[0]->GetChildrenNodes();
		FString CityInfo = PersonInfo[2]->GetContent();
		UE_LOG(LogTemp,Warning,TEXT("Name：%s"),*CityInfo);
		FString CodeNum = PersonInfo[2]->GetAttribute("Code");
		UE_LOG(LogTemp,Warning,TEXT("CodeNum：%s"),*CodeNum);
	}else
	{
		//输出读取失败
		UE_LOG(LogTemp,Warning,TEXT("读取失败"));
	}
	
	
	
}

void ASlateGameModeBase::UpdateXmlData()
{
	FXmlFile XmlFile;
	const FString FilePath = TEXT("D:\\Download\\XMLExample.xml");
	XmlFile.LoadFile(FilePath);

	if (XmlFile.IsValid())
	{
		FXmlNode* RootNode = XmlFile.GetRootNode();
		if (RootNode)
		{
			// 获取第一个人的所有子节点
			TArray<FXmlNode*> PersonNodes = RootNode->GetChildrenNodes();
			if (PersonNodes.Num() > 0)
			{
				FXmlNode* FirstPersonNode = PersonNodes[0];
				TArray<FXmlNode*> ChildNodes = FirstPersonNode->GetChildrenNodes();
				// 查找 <city> 元素
				for (FXmlNode* ChildNode : ChildNodes)
				{
					FString NodeName = ChildNode->GetTag();

					if (NodeName.Equals(TEXT("city"), ESearchCase::IgnoreCase))
					{
						// 修改属性
						TArray<FXmlAttribute> NewAttributes;
						NewAttributes.Add(FXmlAttribute(TEXT("Code"), TEXT("0000")));

						ChildNode->SetAttributes(NewAttributes);
					}
					if (NodeName.Equals(TEXT("name"), ESearchCase::IgnoreCase))
					{
						// 增加属性
						TArray<FXmlAttribute> NewAttributes;
						NewAttributes.Add(FXmlAttribute(TEXT("Gender"), TEXT("Male")));

						ChildNode->SetAttributes(NewAttributes);
					}
				}
				// 保存修改后的 XML 文件
				XmlFile.Save(FilePath);
				XmlFile.Clear();
			}
		}
	}
}

