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
	/*ASIGNING ARRAY IN VECTOR*/
	v=array;
	/*ASIGNING VECTOR IN VECTOR*/
	Vector<double> v1=v;
	double array2[5]= {1,2,3,4,5};
	Vector<double> v2(5);
	v2=array2;

	/*Arithmatical Operation between Vector*/

	Vector<double> v3=v+v1;
	Vector <double> v4= v-v1;
	Vector <double> v5=10.5*v1;
	Vector <double> v6=v1*10.5;
	Vector <double> v7=v1/10.5;


	cout<<"################### VECTOR ONLY ##########3##########"<<endl;

	cout<<"Assigned Array ::Vector0= "<<v<<endl;
	cout<<"Assigned Vector::Vector1= "<<v1<<endl;
	cout<<"Vector of Different Size  :: Vector2= "<<v2<<endl;
	cout<<"Addition of Two Vectors  :: Vector3= "<<v3<<endl;
	cout<<"Subtraction of Two Vectors :: Vector4= "<<v4<<endl;
	cout<<"Double*Vector :: Vector5= "<<v5<<endl;
	cout<<"Vector*Double :: Vector6= "<<v6<<endl;
	cout<<"Vector/Double :: Vector7= "<<v7<<endl;



	Matrix <double>m(3,3);

	std::array<double, 16> array1={1.20,2.10,3,4,5,6,7,8,9,0,11,12,13,14,15,16};
	m=array1.data();

	Matrix <double>m1(3,3);
	m1=m;

	Matrix <double>m2(4,4);
	m2=array1.data();

	/*Arithmatical Operation between Matrices*/

	Matrix<double> m3=m+m1;
	Matrix<double> m4=m-m1;
	Matrix<double> m5=m*m1;
	Matrix<double> m6=m/5.5;
	Matrix<double> m7=m*5.5;


	cout<<"################### MATRIX ONLY ##########3##########"<<endl;

	cout<<"Assigned Array ::Matrix0= \n"<<m<<endl;
	cout<<"Assigned Another Matrix::Matrix1= \n"<<m1<<endl;
	cout<<"Matrix of Different Size :: Matrix2= \n"<<m2<<endl;
	cout<<"Addition of Two Matrices  :: Matrix3= \n"<<m3<<endl;
	cout<<"Subtraction of Two Matrices :: Matrix4= \n"<<m4<<endl;
	cout<<"Matrix*MAtrix :: Matrix5= \n"<<m5<<endl;
	cout<<"Matrix/Double :: Matrix6= \n"<<m6<<endl;
	cout<<"Matrix*Double :: Matrix7= \n"<<m7<<endl;


	cout<<"################### VECTOR and MATRIX ##########3##########"<<endl;

	cout<<"Vector(3) * Matrix(3x3) ="<<v*m<<endl;
	cout<<"Vector(5) * Matrix(4x4) ="<<v2*m2<<endl;
	cout<<"Vector(3) * Matrix(4x4) ="<<v*m2<<endl;
	cout<<"Matrix (3x3) * Matrix (4x4) ="<<m*m2<<endl;



	return 0;
}
