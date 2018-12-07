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

	//Overloaded Flatify to allow the user to get a specified section of the background image
	using Base_Image::Flatify;
	vector<float> Flatify(int startX, int startY, int sizeX, int sizeY);
};

