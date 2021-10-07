#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemData.generated.h"

class UPrimaryItemData;

USTRUCT(BlueprintType)
struct FItemData{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemData")
	TSubclassOf<UPrimaryItemData> PrimaryItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemData")
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemData")
	FGameplayTagContainer ItemTags;
	FItemData();
	FItemData(const TSubclassOf<UPrimaryItemData> PrimaryItemData, const int Amount);
};
