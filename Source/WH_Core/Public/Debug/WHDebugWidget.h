/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Widgets/SCompoundWidget.h"

class SWHDebugWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWHDebugWidget)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);
};