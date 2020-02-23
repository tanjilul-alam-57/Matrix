//============================================================================
// Name        : Matrix_Vector.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Matrix.h"
#include"Vector.h"
#include <array>
using namespace std;

int main() {

	double array[3]= {1.2,2,3};
	Vector<double> v(3);
	v=array;
	cout<<v;
	Matrix <double>m(3,3);
	Matrix <double>m1(3,3);
	std::array<double, 16> array1={1.2,2.5,3,4,5,6,7,8,9,0,11,12,13,14,15,16};
	m=array1.data();
	m1=array1.data();
	Vector <double>v1=v*m;
	cout<<v*m;;
	cout<<m;
	cout<<m*m1;
	return 0;
}
