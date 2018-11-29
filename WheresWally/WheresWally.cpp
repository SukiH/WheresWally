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
	int CurrLine = 0; // A small count system a 

	while (getline(ImageText, Line)) {

		if (CurrLine == LinesRead) {
			stringstream LineStream(Line);
			string Pixel;

			while (getline(LineStream, Pixel, ' ')) {
				if (!Pixel.empty()) {
					cout << Pixel << endl;
					LineVals.push_back(strtof(Pixel.c_str(), 0));
				}
			}

			
			break;
		}
		
		CurrLine++;
		
	}


	return LineVals;
}

int main()
{
	vector<float> TempHold;
	TempHold = FileLine("Cluttered_scene.txt", 1);

	cout << endl;
	cout << "Outputting Contents of Vector" << endl;
	cout << endl;

	for (std::vector<float>::iterator it = TempHold.begin(); it != TempHold.end(); ++it) {
		cout << *it << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
