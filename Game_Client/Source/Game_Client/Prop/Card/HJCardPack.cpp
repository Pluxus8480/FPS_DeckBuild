// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Card/HJCardPack.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Collision/HJCollision.h"
#include "Engine/AssetManager.h"
#include "Card/HJCardData.h"
#include "Game_Client.h"
#include "UI/HJCardChoiceWidget.h"

// Sets default values
AHJCardPack::AHJCardPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_HJTRIGGER);
	Trigger->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));
	if (EffectRef.Object)
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}

	static ConstructorHelpers::FClassFinder<UHJCardChoiceWidget> CardChoiceWidgetClassRef(TEXT("/Game/UI/WBP_CardChoice.WBP_CardChoice_C"));
	if (CardChoiceWidgetClassRef.Class)
		CardChoiceWidgetClass = CardChoiceWidgetClassRef.Class;

	////
///Script/UMGEditor.WidgetBlueprint''	
}

// Called when the game starts or when spawned
void AHJCardPack::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHJCardPack::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}

void AHJCardPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	APlayerController* PlayerController = Cast<APlayerController>(OtherActor->GetOwner());
	if(!PlayerController)
	{
		return;
	}
	HJ_LOG(LogHJDefault, Log, TEXT("%s"), TEXT("Begin"));
	UHJCardChoiceWidget* CardChoiceWidget = CreateWidget<UHJCardChoiceWidget>(GetWorld(), CardChoiceWidgetClass);

	if (CardChoiceWidget)
	{
		CardChoiceWidget->AddToViewport();
		for (const auto& CardData : Cards)
		{
			CardChoiceWidget->AddCard(CardData);
		}
	
	}

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(CardChoiceWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;


	SetActorEnableCollision(false);
	Effect->Activate(true);
	Mesh->SetHiddenInGame(true);

	Effect->OnSystemFinished.AddDynamic(this, &AHJCardPack::OnEffectFinished);
	
}

void AHJCardPack::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!Cards.Num())
	{
		UAssetManager& Manager = UAssetManager::Get();

		TArray<FPrimaryAssetId> Assets;
		Manager.GetPrimaryAssetIdList(TEXT("HJCardData"), Assets);
		ensure(0 < Assets.Num());

		TArray<int32> RandomBox;
		for (int32 i = 0; i < Assets.Num(); ++i)
		{
			RandomBox.Add(i);
		}
		for (int i = 0; i < FMath::Min(RandomBox.Num(), 3); ++i)
		{
			int32 RandomIndex = FMath::RandRange(0, RandomBox.Num() - 1);
			
			FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomBox[RandomIndex]]));
			RandomBox.Swap(RandomIndex, RandomBox.Num() - 1);
			RandomBox.Pop();
			if (AssetPtr.IsPending())
			{
				AssetPtr.LoadSynchronous();
			}
			UHJCardData* Card = Cast<UHJCardData>(AssetPtr.Get());
			if (Card)
			{
				Cards.Add(Card);
			}
		}
	}
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHJCardPack::OnOverlapBegin);
}

// Called every frame
//void AHJCardPack::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

