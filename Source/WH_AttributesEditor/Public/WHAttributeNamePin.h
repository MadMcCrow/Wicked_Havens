/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "WHAttributeName.h"
#include "KismetPins/SGraphPinObject.h"

class SWHAttributeNameWidget;

/**
 *	@class FWHAttributeNameCustomization
 *	Editor Property customisation for attribute name
 *	@see @struct FWHAttributeName
 *	@see @class SWHAttributeNameWidget
 */
class SWHAttributeNamePin : public SGraphPin
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
	void OnAttributeChanged(TSharedPtr<FWHAttributeName> NewAttributeName);

	/** Attribute Name  for pin */
	FWHAttributeName GetDefaultAttributeName() const;

	/** Turn DefaultAttributeName into a string */
	FString GetAttributeNameAsString() const;

};


class FWHAttributeNamePinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin,ESPMode::ThreadSafe> CreatePin(class UEdGraphPin* InPin) const override;

};
