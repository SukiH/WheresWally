/*###############################
Creation Date: 2018-12-02
	Crated Header file

###############################*/

#pragma once
#include "Base_Image.h"
#include <vector>
#include <string>

class Large_Image :	public Base_Image
{
public:
	Large_Image();
	~Large_Image();
	void Output(string fileName, int Q); //output function based on provided function
};

