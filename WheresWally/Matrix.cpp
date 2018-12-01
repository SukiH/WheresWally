/*###############################
Modified Date: 2018-11-29
	Added GetDataPointer function to return the memory address of the matrix, in case that is required, to save on memory
	Added RowCount Function to tell us how many rows are in teh matrix
	Added GetValue which you pass x and y co-ordinates, and it will return the values stored at that location.
Creation Date: 2018-11-28
	Added AddRow Function for added a vector to Data
	Added GetRow Fucntion for Retrieving data from vector
###############################*/

#pragma once
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

vector<float>* Matrix::GetRow(int rowNumber) {
	return &Data[rowNumber];

}

vector<vector<float>>* Matrix::GetDataPointer() {
	return &Data;
}

int Matrix::RowCount() {
	return Data.size();
}

float Matrix::GetValue(int x, int y) {
	return Data[y][x];
}

void Matrix::ChangeColour(int x, int y, float col)
{
	Data[y][x] = col;
}
