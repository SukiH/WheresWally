/*###############################
Author: Suki Harrison
StudentID: 17655881
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

//Function to search for Ref_Image inside of Large_Image, Stores potential Matches in Ref_Image's Locations
/*void LinearNNS(Ref_Image* Search, Large_Image* Background){
	
	float Diff = 0;
	float CurrDiff = 0;
	bool Searching;
	bool firstMatch = false;
	int startX = 0;
	int startY = 0;
	int largestX = 0;
	int largestY = 0;
	int bestX, bestY;
	int SearchRows = Search->RowCount(); //Done to stop calling the method multiple times
	int BackRows = Background->RowCount();
	float TotPx = 0;

	for (int y = 0; y < SearchRows; y++) { //loop to find starting co-ordinates
		if (!(startX == 0)) break;
		for (int x = 0; x < Search->GetRow(0)->size(); x++) {
			if (!(Search->GetValue(x, y) == 255)) { //first value that isn't blank is starting image
				startX = x;
				startY = y;
				break;
			}
		}
	}

	for (int y = 0; y < SearchRows; y++) { //loop to find furthest values that aren't blank
		for (int x = 0; x < Search->GetRow(0)->size(); x++) {
			if ((Search->GetValue(x, y) != 255)) {
				largestX = x;
				largestY = y;
			}
		}
	}


	for (int y = startY; y < BackRows-1; y++) {//Loop through the background to see if we find a pixel colour match, We know we can start in as far as the first value worth searching for
		for (int x = startX; x < Background->GetRow(y)->size()-1; x++){

			if (Search->GetValue(startX, startY) == Background->GetValue(x, y)) {//A Match has been found or the value was the outside of the ref image, and thus not part of what we should be searching.
				CurrDiff = 0;
				Searching = true; //Set value to true
				while (Searching)
				{
					if (((x + largestX) > Background->GetRow(y)->size()) || ((y + largestY) > BackRows)) {
						Searching = false;
						break;
					}


					for (int refY = 0; refY < SearchRows; refY++) { //iterate through reference image
						if (y + refY < BackRows) {
							
							for (int refX = 0; refX < Search->GetRow(refY)->size(); refX++) {
								if (x + refX > Background->GetRow(y)->size()) break;

								if (Background->GetValue(x + refX, y + refY) != 255) {
									if ((refX < startX && refY <= startY) || refX > largestX || refY > largestY) {
									}
									else {
										if (Search->GetValue(refX, refY) != 255) {
											int holdingValue = pow(Background->GetValue((x + refX), (y + refY)) - (Search->GetValue(refX, refY)), 2);
											CurrDiff += holdingValue;
											TotPx++;
										}

									}
								}


							}

						}
					}
					Searching = false;

					CurrDiff = (CurrDiff / TotPx);
 					if (!Searching) {
						if (Diff == 0 || CurrDiff < Diff) {
							Diff = CurrDiff;
							bestX = x;
							bestY = y;
						}
						if (CurrDiff <= 40) Search->AddLocation(x, y, CurrDiff);
					}
				}
			}
		}

	}

	std::cout << "Found Match at X:" << bestX << " And Y:" << bestY << std::endl;
	//DrawSquare(Background, Search, bestX, bestY);

	//string OutputFile = "OutputBest.pgm";
	//Background->Output(OutputFile, 255);
}*/

void NearestNeighbor(Large_Image* Background, Ref_Image* Ref) {
	vector<float> flatRef = Ref->Flatify();
	vector<float> flatBackground = Background->Flatify();
	
	int RefRows = Ref->RowCount(); //Done to stop calling the method multiple times
	int RefCols = Ref->GetRow(0)->size(); //Getting count of columns
	int BackRows = Background->RowCount();
	int BackCols = Background->GetRow(0)->size();
	double dist, sum;
	int BackLoc;


	//Iterate through every section of the background
	for (int bR = 0; bR < (BackRows - RefRows); bR++) {
		for (int bC = 0; bC < (BackCols - RefCols); bC++) {
			sum = 0;
			dist = 0;


			for (int i = 0; i < flatRef.size(); i++) {
				if (flatRef[i] != 255){
					BackLoc = i + (bR*BackCols) + bC;
					sum = sum + pow((flatBackground[BackLoc] - flatRef[i]), 2);
				}
			}

			dist = sqrt(sum); //Euclidean Distance

			Ref->AddLocation(bC, bR, dist);


		}
	}
	
}

//Code that draws a black square on the background image based on given points
void DrawSquare(Large_Image* Image, Ref_Image* Ref, int startX, int startY) { 
	int RefRows = Ref->RowCount(); //Done to stop calling the method multiple times
	int RefCols = Ref->GetRow(0)->size();
	int ImageRows = Image->RowCount();
	int ImageCols = Image->GetRow(0)->size();
	int minY = -3;
	int minX = -3;
	int maxY = 3;
	int maxX = 3;

	if ((startX + minX) < 0) minX = minX - ((startX + minX));
	if ((startY + minY) < 0) minY = minY - ((startY + minY));
	if ((startY + RefRows + maxY) > ImageRows) maxY = (startY + RefRows + 3) - ImageRows-1;
	if ((startX + RefCols + maxX) > ImageCols) maxX = (startX + RefCols + 3) - ImageCols-1;

	//loop through area of image plus a "size 3" border
	for (int y = (startY + minY); y < (startY + RefRows + maxY); y++) {
		for (int x = (startX + minX); x < (startX + RefCols + maxX); x++) {

			//If value is part of the "Border"
			if ((y <= startY) || (y >= (startY + RefRows)) || (x <= startX) || (x >= (startX + RefCols))) {
				Image->ChangeColour(x, y, 0); //Change value to black				
			}
		}
	}

}

//draws squares and outputs pgm for all good locations held in Ref_Image
void OutputAll(Large_Image* Image, Ref_Image* Ref) { 
	for (int i = 0; i < Ref->GetLocations()->size(); i++) {
		CoOrd* CurrLoc = Ref->GetLoc(i);
		Large_Image OutputImage = *Image;
		DrawSquare(&OutputImage, Ref, CurrLoc->x, CurrLoc->y);
		int dist = CurrLoc->dist;
		string fileName = "Output-" + std::to_string(CurrLoc->x) + "-" + std::to_string(CurrLoc->y) + "-" + std::to_string(dist) + ".pgm";
		OutputImage.Output(fileName, 255);
	}

}

void OutputBest(Large_Image* Background, Ref_Image* Ref) {
	int NumLocs = Ref->GetLocations()->size();
	int BestLoc = 0;
	double BestDist = 0;

	for (int i = 0; i < NumLocs; i++) {
		if (i == 0) {
			BestDist = Ref->GetLoc(i)->dist;
			BestLoc = i;
		}
		else{
			if ((Ref->GetLoc(i)->dist) < BestDist) {
				BestDist = Ref->GetLoc(i)->dist;
				BestLoc = i;
			}
		}
	}

	CoOrd* CurrLoc = Ref->GetLoc(BestLoc);
	Large_Image OutputImage = *Background;
	DrawSquare(&OutputImage, Ref, CurrLoc->x, CurrLoc->y);
	int dist = CurrLoc->dist;
	string fileName = "Output-" + std::to_string(CurrLoc->x) + "-" + std::to_string(CurrLoc->y) + "-" + std::to_string(dist) + ".pgm";
	OutputImage.Output(fileName, 255);
}

int main() 
{
	//Temp dummy code for testing functions
	Large_Image* Background = new Large_Image();
	Ref_Image* Wally = new Ref_Image();

	Background->LoadImage("Cluttered_scene.txt");
	Wally->LoadImage("Wally_grey.txt");

	NearestNeighbor(Background, Wally);
	//OutputAll(Background, Wally);
	OutputBest(Background, Wally);

	delete Background;
	delete Wally;



}
