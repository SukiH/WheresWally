/*###############################
Modified Date: 2018-12-02
	Added method allowing the program to change a value of the data. This will be useful when drawing circles around the found location.
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

void Matrix::AddRow(vector<float> Row) { //Adds a vector of floats to the data of the matrix bsaed on the value passed to the parameter
	Data.push_back(Row);
}

vector<float>* Matrix::GetRow(int rowNumber) { //returns the nested vector (The Row)
	return &Data[rowNumber];

}

//The following function returns a pointer to our data in the matrix, as vectors can commonly change their memory addresses with operations are performed
//Having this function allows us to refresh the pointer and help reduce errors.
vector<vector<float>>* Matrix::GetDataPointer() { 
	return &Data;
}

int Matrix::RowCount() { //simple function to get the amount of rows held in this vector
	return Data.size();
}

float Matrix::GetValue(int x, int y) { //gets the value held at point x and y
	return Data[y][x];
}

void Matrix::ChangeColour(int x, int y, float col) //Allows access to change data at point x and y
{
	Data[y][x] = col;
}
