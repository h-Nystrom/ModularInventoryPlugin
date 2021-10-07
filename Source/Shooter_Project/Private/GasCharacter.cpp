// Fill out your copyright notice in the Description page of Project Settings.
#include "GasCharacter.h"
#include <GameplayEffectTypes.h>
#include "GasSystemComponent.h"
#include "GasAbilityInputID.h"
#include "GasAttributeSet.h"

	AGasCharacter::AGasCharacter(){
		AbilitySystemComponent = CreateDefaultSubobject<UGasSystemComponent>("AbilitySystemComponent");
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
		AttributeSet = CreateDefaultSubobject<UGasAttributeSet>("Attributes");
	}

	UAbilitySystemComponent* AGasCharacter::GetAbilitySystemComponent() const{
		return AbilitySystemComponent;
	}

	void AGasCharacter::InitializeAttributes(){
		
		if(AbilitySystemComponent && DefaultAttributeEffect){
			
			auto ContextHandle = AbilitySystemComponent->MakeEffectContext();
			ContextHandle.AddSourceObject(this);

			const auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect,1,ContextHandle);
			
			if(SpecHandle.IsValid()){
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
	void AGasCharacter::GrantAbility(const TSubclassOf<UGameplayAbility> GameplayAbility, const int Level) const{
		if(HasAuthority() && GameplayAbility)
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GameplayAbility, Level));
	}

	void AGasCharacter::RemoveAbilityBySpecHandle(const FGameplayAbilitySpecHandle AbilitySpecHandle) const{
		if(HasAuthority() && AbilitySpecHandle.IsValid()){
			AbilitySystemComponent->SetRemoveAbilityOnEnd(AbilitySpecHandle);
		}
	}

	void AGasCharacter::PossessedBy(AController* NewController){
		Super::PossessedBy(NewController);

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
	}

	void AGasCharacter::OnRep_PlayerState(){
		Super::OnRep_PlayerState();
		
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();

		if(AbilitySystemComponent && InputComponent){
			const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGasAbilityInputID",
				static_cast<int32>(EGasAbilityInputID::Confirm), static_cast<int32>(EGasAbilityInputID::Cancel));
			AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent,Binds);
		}
	}
	
