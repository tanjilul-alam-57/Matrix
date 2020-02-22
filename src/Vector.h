/*
 * Vector.h
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <cstdint>
#include <cstring>
using namespace std;
#include <iostream>
#include"Matrix.h"
class Vector{
public:
	Vector(int);
	Vector();
	~Vector();
	Vector(const Vector&);
	friend std::ostream& operator<<(std::ostream&, const Vector&);
	friend std::istream& operator>>(std::istream&, Vector&);
	Vector& operator=(int buffer[]);
	Vector& operator=(const Vector&);
	Vector& operator*=(double);
	Vector& operator/=(double);
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	friend Vector operator*=(const Vector &,const Matrix&);
protected:
	int m_size;
	double *v_array;
	void allocSpace();
};
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(const Vector&, double);
Vector operator*(double, const Vector&);
Vector operator/(const Vector&, double);
Vector operator*(const Vector& v1, const Matrix& m2);
#endif /* VECTOR_H_ */
