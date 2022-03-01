/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "EdGraphUtilities.h"
#include "SGraphPin.h"
#include "WHAttributeName.h"
#include "KismetPins/SGraphPinObject.h"


struct FWHAttributeName;

class SWHAttributeNamePin : public SGraphPinObject
{
public:
	SLATE_BEGIN_ARGS(SWHAttributeNamePin) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	virtual FSlateColor GetPinColor() const override {return FSlateColor(FColor::Silver);}

private:
	/** Called on Attribute name changed  for default value */
	void OnAttributeChanged(TSharedPtr<FWHAttributeName> NewAttributeName, ESelectInfo::Type Arg);

	/** Attribute Name  for pin */
	FWHAttributeName DefaultAttributeName;
	/** Turn DefaultAttributeName into a string */
	FString GetAttributeNameAsString() const;
};


class FWHAttributeNamePinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin,ESPMode::ThreadSafe> CreatePin(class UEdGraphPin* InPin) const override;

};
