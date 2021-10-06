#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SlotData.generated.h"

class UBaseItemData;
USTRUCT(BlueprintType)
struct FSlotData{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemSlot")
	TSubclassOf<UBaseItemData> BaseItemDataRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemSlot")
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemSlot")
	FGameplayTagContainer ItemTags;
	FSlotData();
	FSlotData(const TSubclassOf<UBaseItemData> BaseItemData, const int Amount);
};
