/*
 * Vector.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#include "Vector.h"

Vector::Vector(int size) : m_size(size){
	allocSpace();

	for (int i = 0; i < m_size; ++i) {
		v_array[i] = 0;
	}

}
Vector::~Vector() {
	delete[] v_array;
}
Vector::Vector():m_size(1) {

	allocSpace();
	v_array[0] = 0;
}

Vector::Vector(const Vector& v):m_size(v.m_size)
{
	allocSpace();
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = v.v_array[i];
	}

}

Vector& Vector::operator =(int buffer[])

{
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = buffer[i];
	}
	return *this;
}

Vector& Vector::operator =(const Vector& v) {

	if (this == &v) {
		return *this;
	}

	if (m_size != v.m_size ) {
		for (int i = 0; i < m_size; ++i) {
			delete[] v_array;
		}
		delete[] v_array;

		m_size = v.m_size;
		allocSpace();
	}

	for (int i = 0; i < m_size; ++i) {

		v_array[i] = v.v_array[i];
	}

	return *this;
}

Vector& Vector::operator *=(double num) {

	for (int i = 0; i < m_size; ++i) {

		v_array[i] *= num;

	}
	return *this;
}

Vector& Vector::operator /=(double num) {
	for (int i = 0; i < m_size; ++i) {

		v_array[i] /= num;

	}
	return *this;
}

Vector& Vector::operator +=(const Vector& v) {
	for (int i = 0; i < m_size; ++i) {
		v_array[i] += v.v_array[i];

	}
	return *this;

}

Vector& Vector::operator -=(const Vector& v) {
	for (int i = 0; i < m_size; ++i) {
		v_array[i] -= v.v_array[i];
	}
	return *this;
}



void Vector::allocSpace() {

	v_array = new double[m_size];
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = 0;
	}
}




ostream& operator<<(ostream& os, const Vector& v)
{
	for (int i = 0; i < v.m_size; ++i) {
		os << v.v_array[i]<<" ";
	}
	os << endl;
	return os;
}

istream& operator>>(istream& is, Vector& v)
{
	for (int i = 0; i < v.m_size; ++i)  {
		is >> v.v_array[i];
	}
	return is;
}
Vector operator +(const Vector& v1, const Vector& v2) {

	Vector temp(v1);
	return (temp += v2);
}

Vector operator -(const Vector& v1, const Vector& v2) {

	Vector temp(v1);
	return (temp -= v2);
}

Vector operator *(const Vector & v, double num) {

	Vector temp(v);
	return (temp *= num);

}

Vector operator *(double num, const Vector& v) {
	return (v * num);
}

Vector operator /(const Vector& v, double num) {
	Vector temp(v);
	return (temp /= num);
}
Vector operator*=(const Vector & v,const Matrix& m){


    Vector temp(m.m_colum);
    for (int i = 0; i < m.m_colum; ++i) {
        for (int j = 0; j < m.m_row; ++j) {

                temp.v_array[i] += (v.v_array[j] * m.m_array[j][i]);

        }
    }
    return temp;

}

Vector operator*(const Vector& v1, const Matrix& m2)
{
    Vector temp(v1);
    return (temp *= m2);
}
