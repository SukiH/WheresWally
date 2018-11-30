/*###############################
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

void Ref_Image::AddLocation(int x, int y)
{
	CoOrd NewLoc{ x, y };
	Locations.push_back(NewLoc);
}

