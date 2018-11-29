/*###############################
Creation Date: 2018-11-29
	Set Base Image to inherit Matrix
	Added header for LoadImage function

###############################*/

#pragma once
#include "Matrix.h"

class Base_Image : public Matrix
{
private:
	Matrix data();
public:
	Base_Image();
	~Base_Image();
	void LoadImage(string);
};

