// Fill out your copyright notice in the Description page of Project Settings.


#include "GasAttributeSet.h"
#include "Net/UnrealNetwork.h"


	UGasAttributeSet::UGasAttributeSet(){}

	void UGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Health, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	}

	void UGasAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth){
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Health, OldHealth);
	}

	void UGasAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina){
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Stamina, OldStamina);
	}

	void UGasAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength){
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Strength, OldStrength);
	}