/*###############################
Creation Date: 2018-11-29
	Set Base Image to inherit Matrix
	Added header for LoadImage function

###############################*/

#pragma once
#include "Matrix.h"
#include "string"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class Base_Image : public Matrix
{

private:
public:
	Base_Image();
	~Base_Image();
	void LoadImage(string);
	void operator +(vector<float>&);
	//Takes the data of the image and returns a 1d vector of all the data in the iamge
	vector<float> Flatify();
};

