/*###############################
Modified Date: 2018-11-29
	Added New methods for retrieving data
Creation Date: 2018-11-21
	Created Initial header structure for our matrix class
###############################*/

#pragma once
#include <vector>

using namespace std;
class Matrix
{
private:
	vector<vector<float>> Data;
public:
	Matrix();
	~Matrix();
	void AddRow(vector<float>); //Adds a row to the vector based on a pre-filled row
	vector<vector<float>>* GetDataPointer(); //Gets a pointer to the full set of data in the Matrix. Uses pointer to save on memory
	vector<float>* GetRow(int);
	int RowCount();
	float GetValue(int x, int y);
	void ChangeColour(int x, int y, float col);
};

