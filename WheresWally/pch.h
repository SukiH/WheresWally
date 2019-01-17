/*###############################
Modified Date: 2018-12-19
	Ensured that all intented headers and methods are included
Creation Date: 2018-11-20
	Created pch.h and included all headers that we intend to use
###############################*/

#pragma once
#include "Matrix.h"
#include "Base_Image.h"
#include "Large_Image.h"
#include "Ref_Image.h"
#include "Struct.h"

void DrawSquare(Large_Image* Image, Ref_Image* Ref, int startX, int startY);
void LinearNNS(Ref_Image* Search, Large_Image* Background);
void MergeSort(vector<CoOrd>* data);