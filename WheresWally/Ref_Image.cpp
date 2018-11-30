/*###############################
Creation Date: 2018-11-20

###############################*/

#include "pch.h"
#include "Ref_Image.h"

Ref_Image::Ref_Image()
{
}

Ref_Image::~Ref_Image()
{
}

vector<int[2]>* Ref_Image::GetLocations() {
	return &Locations;
}

int* Ref_Image::GetLoc(int Coordinate) {
	return Locations[Coordinate];
}
