/*###############################
Creation Date: 2018-11-20

###############################*/

#pragma once
#include "Base_Image.h"

class Ref_Image : public Base_Image
{
private:
	vector<int[2]> Locations;
public:
	Ref_Image();
	~Ref_Image();
	vector<int[2]>* GetLocations();
	int* GetLoc(int);


};

