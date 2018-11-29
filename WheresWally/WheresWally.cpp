/*###############################
Author: Suki Harrison
StudentID: 17655881
Modified: 2018-11-28
	Added Method to retrieve a line data from file
		-Done line by line to be reusable with different file sizes.
		-Memory shouldn't be an issue as in C++11, data is moved when returned from a function, 
			not copied. Worth noting that this could cause efficiency problems pre C++11
Creation Date: 2018-11-20
	Created Project
	-Added empty classes and their PCHs for use later - Creating solution structure
	-Prepared pch.h as wrapper for all headers.
	-Added Matrix class for holding image data.
###############################*/

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
vector<float> FileLine(string FileName, int LinesRead = 0) { //
	ifstream ImageText(FileName); //Set ifstream to file specified

	if (!ImageText.is_open()) { //Check that the file is open 
		cout << "Unable to Open File" << endl;//Let user know of error
	}

	vector<float> LineVals; //This will contain the values and be the vector we ultimately return
	string Line; // To hold a line of data, so that we can then do a nested operation and get data from inside that line
	int CurrLine = 0; // A small count system to allow us to work out how many lines through the file we are

	while (getline(ImageText, Line)) { //Read a line into the system

		if (CurrLine == LinesRead) { //Check if we have reached the next file needed to be read
			stringstream LineStream(Line);
			string Pixel;

			while (getline(LineStream, Pixel, ' ')) {
				if (!Pixel.empty()) { //Checks if there is no data in the value that was read
					LineVals.push_back(strtof(Pixel.c_str(), 0)); //Adds value to vector
				}
			}

			
			break; //Line has been read, break loop
		}
		
		CurrLine++; //Increment counter
		
	}


	return LineVals; //return vector, for use in a Matrix's vector of vectors of floats
}

int main() 
{
	//Temp dummy code for testing functions
	Base_Image* Image = new Base_Image();

	Image->LoadImage("Cluttered_scene.txt");
	//Image->AddRow(FileLine("Cluttered_scene.txt", 0));

	cout << endl;
	cout << "Outputting Contents of Vector" << endl;
	cout << endl;

	

	for (int i = 767; i < Image->RowCount(); i++) {
		cout << Image->GetRow(i)->size() << endl;
		for (std::vector<float>::iterator it = Image->GetRow(i)->begin(); it != Image->GetRow(i)->end(); ++it) {
			cout << *it << endl;
		}
	}
	
}
