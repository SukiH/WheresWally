/*###############################
Creation Date: 2018-11-20

###############################*/

#include "pch.h"
#include "Large_Image.h"

Large_Image::Large_Image(){
}

Large_Image::~Large_Image(){
}

void Large_Image::Output(char *filename, int Q)
{
	//based highly upon Presupplied Function, provided for assignment.
// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.


	int i, j;
	unsigned char *image;
	vector<vector<float>>* Data = GetDataPointer();
	std::ofstream myfile;
	int sizeR = Data->size();
	int sizeC = Data[0].size();

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i < sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!myfile) {
		std::cout << "Can't open file: " << filename << std::endl;
		exit(1);
	}

	myfile << "P5" << std::endl;
	myfile << sizeC << " " << sizeR << std::endl;
	myfile << Q << std::endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << std::endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}
