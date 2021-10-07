// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GasCharacter.generated.h"

UCLASS(Blueprintable,config=Game)
class AGasCharacter : public ACharacter, public IAbilitySystemInterface{

		GENERATED_BODY()
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UGasSystemComponent* AbilitySystemComponent;
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
		class UGasAttributeSet* AttributeSet;

	public:

		AGasCharacter();
		
		virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

		virtual void InitializeAttributes();
		virtual void PossessedBy(AController* NewController) override;
		virtual void OnRep_PlayerState() override;
	
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category= "GAS")
			TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category= "GAS")
			TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
		
		

		UFUNCTION(BlueprintCallable,Category="GAS")
			void GrantAbility(TSubclassOf<UGameplayAbility> GameplayAbility, int Level) const;
	
		UFUNCTION(BlueprintCallable,Category="GAS")
			void RemoveAbilityBySpecHandle(const FGameplayAbilitySpecHandle AbilitySpecHandle) const;
};
