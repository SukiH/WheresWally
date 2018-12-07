/*###############################
Modified Date: 2018-12-03
	Changed AddLocation Method to reflect the CoOrd Struct
Creation Date: 2018-11-30
	Added Ref Image Class to project. Inherits Base Image.
###############################*/

#include "pch.h"
#include "Ref_Image.h"

Ref_Image::Ref_Image()
{
}

Ref_Image::~Ref_Image()
{
}

vector<CoOrd>* Ref_Image::GetLocations()
{
	return &Locations;
}

CoOrd * Ref_Image::GetLoc(int LocNum)
{
	return &Locations[LocNum];
}

void Ref_Image::AddLocation(int x, int y, double dist)
{
	CoOrd NewLoc{ x, y, dist };
	Locations.push_back(NewLoc);
}

