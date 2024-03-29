/*###############################
Author: Suki Harrison
StudentID: 17655881
Modified Date: 2018-12-20
	Changed NNS to use overloaded function of matrix
Modified Date: 2018-12-19
	Created a Merge Sort Algorithm for sorting Vectors of Type CoOrd
Modified Date: 2018-12-03
	Added the NearestNeighbourSearch method.
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
#include <algorithm>


//Gets the next line of a specified text file. The line this will read is LinesRead + 1
vector<float> FileLine(string FileName, int LinesRead = 0) { //
	ifstream ImageText(FileName); //Set ifstream to file specified

	if (!ImageText.is_open()) { //Check that the file is open 
		std::cout << "Unable to Open File" << std::endl;//Let user know of error
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

void LinearNNS(Ref_Image* Ref, Large_Image* Background) {

	float Diff = 0;
	float CurrDiff = 0;
	bool Searching;
	bool firstMatch = false;
	int largestX = 0;
	int largestY = 0;
	int bestX, bestY;
	int RefRows = Ref->RowCount(); //Done to stop calling the method multiple times
	int BackRows = Background->RowCount();
	int BackCols = Background->GetRow(0)->size();
	int RefCols = Ref->GetRow(0)->size();
	float TotPx = 0;


	for (int y = 0; y < BackRows - 1 - RefRows; y++) {//Loop through the background to see if we find a pixel colour match, We know we can start in as far as the first value worth searching for
		for (int x = 0; x < BackCols - 1 - RefCols; x++) {
				Searching = true; //Set value to true
				while (Searching)
				{
					CurrDiff = 0;
					for (int refY = 0; refY < RefRows; refY++) { //iterate through reference image
						if (y + refY < BackRows) {
							for (int refX = 0; refX < RefCols; refX++) {
								if (x + refX > BackCols) break;
								if ((*Ref)(refX, refY) != 255) {
									float holdingValue = pow((*Background)((x + refX), (y + refY)) - ((*Ref)(refX, refY)), 2);
									CurrDiff += holdingValue;
									TotPx++;
								}
							}

						}
					}
					Searching = false;

					CurrDiff = (CurrDiff) / TotPx;
					if (Searching) {
						
					}
				}
				if (((Ref->GetLocations()->size() == 0) && Diff == 0) || CurrDiff < Diff) {
					Diff = CurrDiff;
					bestX = x;
					bestY = y;
					
				}
				Ref->AddLocation(x, y, CurrDiff);
		}

	}
}

//Code that draws a black square on the background image based on given points
void DrawSquare(Large_Image* Image, Ref_Image* Ref, int startX, int startY, int LineSize = 3) { 
	int RefRows = Ref->RowCount(); //Done to stop calling the method multiple times
	int RefCols = Ref->GetRow(0)->size();
	int ImageRows = Image->RowCount();
	int ImageCols = Image->GetRow(0)->size();
	int minY = -LineSize;
	int minX = -LineSize;
	int maxY = LineSize;
	int maxX = LineSize;

	if ((startX + minX) < 0) minX = minX - ((startX + minX));
	if ((startY + minY) < 0) minY = minY - ((startY + minY));
	if ((startY + RefRows + maxY) > ImageRows) maxY = (startY + RefRows + maxY) - ImageRows-1;
	if ((startX + RefCols + maxX) > ImageCols) maxX = (startX + RefCols + maxX) - ImageCols-1;

	//loop through area of image plus a "size 3" border
	for (int y = (startY + minY); y < (startY + RefRows + maxY); y++) {
		for (int x = (startX + minX); x < (startX + RefCols + maxX); x++) {

			//If value is part of the "Border"
			if ((y <= startY) || (y >= (startY + RefRows)) || (x <= startX) || (x >= (startX + RefCols))) {
				if (y < ImageRows && x < ImageCols) {
					Image->ChangeColour(x, y, 0); //Change value to black				
				}
			}
		}
	}

}

//Inner part of Suki's merge sort algorithm to sort data
void MergeCombine(vector<CoOrd>* data, int lowVal, int midVal, int hiVal) {
	int vectSize = hiVal - lowVal + 1;
	vector<CoOrd> temp(vectSize); //create a new vector as a temporary holding set
	int left = lowVal, right = midVal + 1;//Markers for where to start searching from in the left and right halves of the array.
	int k = 0;//current value in temp array

	while (left <= midVal && right <= hiVal) {
		double dataLeftDist = (*data)[left].dist; //get dist of the left hand data
		double dataRightDist = (*data)[right].dist; //get dist of the right hand data
		if (dataLeftDist <= dataRightDist) { //compare distances
			temp[k++] = (*data)[left++];
		}
		else {
			temp[k++] = (*data)[right++];
		}
	}

	while (left <= midVal) //check through the rest of the left side
	{
		temp[k++] = (*data)[left++];
	}

	while (right <= hiVal) //check through the rest of the right side
	{
		temp[k++] = (*data)[right++];
	}

	for (k = 0, left = lowVal; left <= hiVal; ++left, ++k) {
		(*data)[left] = temp[k]; //place sorted values back into vector
	}
}

//Break given data into two halves to then be sorted
void MergeBreaker(vector<CoOrd>* data, int lowVal, int hiVal) {
	int midVal;
	if (lowVal < hiVal) { //if invalid, don't need to sort
		midVal = (lowVal + hiVal) >> 1; //bitshift oncce right to get midway point
		MergeBreaker(data, lowVal, midVal); //continue to break down and sort the left side
		MergeBreaker(data, midVal + 1, hiVal); //continue to break down and sort the right side
		MergeCombine(data, lowVal, midVal, hiVal); //once all lower sections have been sorted, combine what is left
	}
}

//Merge sort for a vector of CoOrd. As data is by pointers, it will not use that much more memory, and also will affect the originally provided data directly
void MergeSort(vector<CoOrd>* data) {
	int dataSize = data->size();
	MergeBreaker(data, 0, (dataSize - 1)); //take given data and break it down
}

//Outputs the best N locations held in Ref_Image where the image was found in the Large_Image
void OutputBest(Large_Image* Background, Ref_Image* Ref, int n) {
	Large_Image OutputImage = *Background;
	for (int i = 0; i < n; i++) {
		CoOrd* CurrLoc = Ref->GetLoc(i);
		double dist = CurrLoc->dist;
		DrawSquare(&OutputImage, Ref, CurrLoc->x, CurrLoc->y, 1);
		if (i == 0) {
			std::cout << "Best Match at X:" << CurrLoc->x << " And Y:" << CurrLoc->y << " With a distance of:" << dist << std::endl;
		}
	}	
	string fileName = "Output-" + std::to_string(n) + "Best.pgm";

	std::cout << "Outputting PGM file to: " << fileName << std::endl;
	OutputImage.Output(fileName, 255);
}

int main() 
{
	//Temp dummy code for testing functions
	Large_Image* Background = new Large_Image();
	Ref_Image* Wally = new Ref_Image();

	Background->LoadImage("Cluttered_scene.txt");
	Wally->LoadImage("Wally_grey.txt"); 

	LinearNNS(Wally, Background); //search for all locations
	Wally->SortLocations(); //sort locations
	string userChoice;
	bool validSelection = false;

	std::cout << std::endl;
	std::cout << "Welcome to Where's Wally" << std::endl; //greet user

	while (!validSelection) {
		std::cout << std::endl;
		std::cout << "Please enter 1 to only get the best match." << std::endl << "Please enter 2 to be able to provide how many matches you wish to search for" << std::endl;
		std::cin >> userChoice;
		std::cout << std::endl;

		if (userChoice == "1") {
			validSelection = true;
			OutputBest(Background, Wally, 1);
		}
		else if (userChoice == "2") {
			validSelection = true;
			int userN;
			int numVals = 10;
			std::cout << "Please enter an integer value for the N number of matches you wish to have displayed" << std::endl;
			std::cin >> userN;
			std::cout << std::endl;
			numVals = userN;
			OutputBest(Background, Wally, numVals);
		}
		else {
			validSelection = false;
			std::cout << "Invalid Selection" << std::endl;
		}
		
	}

	std::cout << std::endl;
	std::cout << "Thank you for using the Where's Wally NNS Application." << std::endl << "Have a nice day" << std::endl;

	delete Background;
	delete Wally;

	system("pause");
}
