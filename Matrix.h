/*
* Matrix.h
* 9/21/2022
* Written by AwesomeMc101 for LunarGuard LLC
* Licensed under MIT
*/

#include <vector>
#include <string>

class Matrix
{
public:
	std::string name;
	int rows, cols;
	std::vector<double> vals; 
	/*
	[ 0 1 2 ]
	[ 3 4 5 ]
	
	Pos Example ^
	*/

};

Matrix newMatrix(int rows, int cols)
{
	Matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	return mat;
}

Matrix newMatrix(int rows, int cols, std::vector<double> vals)
{
	Matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	mat.vals = vals;
	return mat;
}