/*###############################
Creation Date: 2018-11-29
	Added load image function to read any image in a file, and load the data in the same 2d format as the image was supplied. 
		*** N.B. May consider coming back and changing this function at some point to use 
		*** vector.append if we can find a way to determine how large an image will be before we use it.
###############################*/

#include "pch.h"
#include "Base_Image.h"



Base_Image::Base_Image()
{
}

Base_Image::~Base_Image()
{
}

void Base_Image::LoadImage(string FilePath) {
	ifstream ImageText(FilePath); //Set ifstream to file specified

	if (!ImageText.is_open()) { //Check that the file is open 
		//error
	}
	else {

		vector<float> LineVals; //This will contain the values and be the vector we ultimately return
		string Line; // To hold a line of data, so that we can then do a nested operation and get data from inside that line
		string Pixel;

		
		cout << "Loading...";
		while (!ImageText.eof()) {//loop until we have full set of data.
			while (getline(ImageText, Line, '\n')) { //Read a line into the system

				
				stringstream LineStream(Line);
				Pixel = "";

				while (getline(LineStream, Pixel, ' ')) {
					
					if (!Pixel.empty()) { //Checks if there is no data in the value that was read
						LineVals.push_back(strtof(Pixel.c_str(), 0)); //Adds value to vector
					}
				}


				
				AddRow(LineVals); //Add row
				LineVals.clear();
				break; //Line has been read, break loop
			}

			//cout << ".";
		}
		cout << endl;
		
		
	}
}

vector<float> Base_Image::Flatify() {
	vector<float> Flattened;

	int Rows = RowCount();
	int Cols = GetRow(0)->size();


	for (int r = 0; r < Rows; r++) {
		for (int c = 0; c < Cols; c++) {
			Flattened.push_back(GetValue(c, r));
		}
	}

	return Flattened;
}


