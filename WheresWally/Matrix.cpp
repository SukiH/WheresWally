/*###############################
Creation Date: 2018-11-28
	Added AddRow Function for added a vector to Data


###############################*/

#include "pch.h"
#include "Matrix.h"


Matrix::Matrix()
{
	
}


Matrix::~Matrix()
{
}

void Matrix::AddRow(vector<float> Row) { //Adds a presupplied vector of floats to the data of the matrix
	Data.push_back(Row);
}

vector<vector<float>>* Matrix::GetDataPointer() {
	return &Data;
}
