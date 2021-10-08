#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PrimaryItemData.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	UPrimaryItemData* PrimaryItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FGameplayTagContainer ItemTags;
	FItemData();
	FItemData(UPrimaryItemData* PrimaryItemData, const int Amount);
	FItemData(const FItemData& ItemData);
	void KeepTag(const FItemData& ItemSlot);
};
