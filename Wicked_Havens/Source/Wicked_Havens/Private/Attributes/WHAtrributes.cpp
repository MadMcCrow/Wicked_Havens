// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/WHAttributes.h"



bool FWHAttribute::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    Ar << BaseValue;
    Ar << Value;
    return true;
}