/*###############################
Creation Date: 2018-12-02
	Created Large Image class, inheriting from Base Image.
	Added output file, based on pre-supplied function

###############################*/

#include "pch.h"
#include "Large_Image.h"

Large_Image::Large_Image(){
}

Large_Image::~Large_Image(){
}

void Large_Image::Output(string filename, int Q)
{
	//based highly upon Presupplied Function, provided for assignment.
// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.


	//int i, j;
	unsigned char *image;
	vector<vector<float>>* Data = GetDataPointer();
	std::ofstream myfile;
	int sizeR = Data->size();
	int sizeC = Data->at(0).size();

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	int ctr = 0;
	for (int cn = 0; cn < sizeR; cn++) {
		for (std::vector<float>::iterator it = GetRow(cn)->begin(); it != GetRow(cn)->end(); ++it) {
			image[ctr] = (unsigned char)*it;
			ctr++;
		}
	}

	myfile.open(filename.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

	if (!myfile.is_open()) {
		std::cout << "Can't open file: " << filename << std::endl;
		myfile.close();
		exit(1);
	}

	myfile << "P5" << std::endl;
	myfile << sizeC << " " << sizeR << std::endl;
	myfile << Q << std::endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << std::endl;
		myfile.close();
		exit(0);
	}

	myfile.close();

	delete[] image;
}

vector<float> Large_Image::Flatify(int startX, int startY, int sizeX, int sizeY)
{
	vector<float> Flattened;

	int Rows = RowCount();
	int Cols = GetRow(0)->size();

	if (!(startY + sizeY >= Rows) || !(startX + sizeX >= Cols)) {
		for (int r = startY; r < (startY + sizeY); r++) {
			for (int c = startX; c < (startX + sizeX); c++) {
				Flattened.push_back(GetValue(c, r));
			}
		}
	}

	return Flattened;
}
