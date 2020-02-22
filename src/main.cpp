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

	int array[4]= {1,2,3,4};
	Vector v(4);
	v=array;
	cout<<v;
	Matrix m(3,3);
	Matrix m1(3,3);
	std::array<int, 16> array1={1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16};
	m=array1.data();
	m1=array1.data();
	cout<<2*m1*m+m1+m;
	return 0;
}
