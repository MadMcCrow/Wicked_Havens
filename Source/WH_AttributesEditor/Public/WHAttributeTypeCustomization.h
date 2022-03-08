/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

struct FWHAttributeType;
class SWHAttributeTypeWidget;

/**
 *	@class FWHAttributeTypeCustomization
 *	Editor Property customisation for Attribute Types
 *	@see @struct FWHAttributeType
 *	@see @class SWHAttributeTypeWidget
 */
class FWHAttributeTypeCustomization : public IPropertyTypeCustomization, public FEditorUndoClient
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable( new FWHAttributeTypeCustomization );
	}


	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;
	virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;

private:
	/**
	 * Handle to the actual Property being edited (ie the attribute)
	 */
	TSharedPtr<IPropertyHandle> AttributeTypePropertyHandle;

	// Get Current Edited AttributeType property value
	FWHAttributeType GetEditedAttributeType() const;

	// Called when changed Attribute Name part of Attribute
	void OnAttributeTypeChanged(TSharedPtr<FWHAttributeType> NewName) const;

};
