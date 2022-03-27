/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "WHAttribute.h"
#include "KismetPins/SGraphPinObject.h"

class SWHAttributeRefWidget;

/**
 *	@class SWHAttributeRefPin
 *	Editor Property customisation for attribute name
 *	@see @struct FWHAttributeRef
 *	@see @class SWHAttributeRefWidget
 */
class SWHAttributeRefPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SWHAttributeRefPin) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	virtual FSlateColor GetPinColor() const override;

private:
	/** Called on Attribute name changed  for default value */
	void OnAttributeRefChanged(TSharedPtr<FWHAttributeRef> NewAttributeRef);

	/** Attribute Name  for pin */
	FWHAttributeRef GetDefaultAttributeRef() const;

	/** Turn DefaultAttributeName into a string */
	FString GetAttributeRefAsString() const;

};


class FWHAttributeRefPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin,ESPMode::ThreadSafe> CreatePin(class UEdGraphPin* InPin) const override;

};
