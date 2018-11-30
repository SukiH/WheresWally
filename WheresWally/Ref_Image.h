/*###############################
Creation Date: 2018-11-30
	Added Ref Image Header. Inherits Base_image.

###############################*/

#pragma once
#include "Base_Image.h"
#include "Struct.h"

class Ref_Image : public Base_Image
{
private:
	vector<CoOrd> Locations;
public:
	Ref_Image();
	~Ref_Image();
	vector<CoOrd>* GetLocations();
	CoOrd* GetLoc(int);
	void AddLocation(int, int);
};

