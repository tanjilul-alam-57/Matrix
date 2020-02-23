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
template<class T>
class Vector{
public:
	Vector(int);
	Vector();
	~Vector();
	Vector(const Vector&);
	template<class U>
	friend std::ostream& operator<<(std::ostream&, const Vector<U>&);
	template<class U>
	friend std::istream& operator>>(std::istream&, Vector<U>&);
	Vector& operator=(T buffer[]);
	Vector& operator=(const Vector&);
	Vector& operator*=(double);
	Vector& operator/=(double);
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	template<class U>
	friend Vector<U> operator*=(const Vector<U> &,const Matrix<U>&);
	template<class U>
	friend Vector<U> operator*(const Vector<U>& v1, const Matrix<U>& m2);
	int m_size;
	T *v_array;
	void allocSpace();
};

template<class T>
Vector<T>::Vector(int size) : m_size(size){
	allocSpace();

	for (int i = 0; i < m_size; ++i) {
		v_array[i] = 0;
	}

}
template<class T>
Vector<T>::~Vector() {
	delete[] v_array;
}
template<class T>
Vector<T>::Vector():m_size(1) {

	allocSpace();
	v_array[0] = (T*)0;
}
template<class T>
Vector<T>::Vector(const Vector& v):m_size(v.m_size)
{
	allocSpace();
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = v.v_array[i];
	}

}

/*
 * assign any array of same size
 */

template<class T>
Vector<T>& Vector<T>::operator =(T buffer[])

{
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = buffer[i];
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator =(const Vector& v) {

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

		v_array[i] = (T*)v.v_array[i];
	}

	return *this;
}


template<class T>

Vector<T>& Vector<T>::operator *=(double num) {

	for (int i = 0; i < m_size; ++i) {

		v_array[i] *= num;

	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator /=(double num) {
	for (int i = 0; i < m_size; ++i) {

		v_array[i] /= num;

	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator +=(const Vector& v) {
	for (int i = 0; i < m_size; ++i) {
		v_array[i] += v.v_array[i];

	}
	return *this;

}
template<class T>
Vector<T>& Vector<T>::operator -=(const Vector& v) {
	for (int i = 0; i < m_size; ++i) {
		v_array[i] -= v.v_array[i];
	}
	return *this;
}

template<class T>

void Vector<T>::allocSpace() {

	v_array = new T[m_size];
	for (int i = 0; i < m_size; ++i) {
		v_array[i] = 0;
	}
}


///////////Non-Member functions ///////////////

/*
 * Operator Overloading for printing Vector
 */
template<class T>

std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
	for (int i = 0; i < v.m_size; ++i) {
		os << v.v_array[i]<<" ";
	}
	os << endl;
	return os;
}

/*
 * Operator Overloading inserting element of the vector
 * std::cin has been used here
 *
 */

template<class T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
	for (int i = 0; i < v.m_size; ++i)  {
		is >> (T*)v.v_array[i];
	}
	return is;
}
/*
 * Vector of same Size can be added
 */

template<class T>
Vector<T> operator +(const Vector<T>& v1, const Vector<T>& v2) {

	Vector<T> temp(v1);
	return (temp += v2);
}
/*
 * Subtract two vectors
 */
template<class T>
Vector<T> operator -(const Vector<T>& v1, const Vector<T>& v2) {

	Vector<T> temp(v1);
	return (temp -= v2);
}

/*
 * Vector * number multiplication
 */

template<class T>
Vector<T> operator *(const Vector<T> & v, double num) {

	Vector<T> temp(v);
	return (temp *= num);

}
/*
 * number*Vector multiplication
 */

template<class T>
Vector<T> operator *(double num, const Vector<T>& v) {
	return (v * num);
}
template<class T>
Vector<T> operator /(const Vector<T>& v, double num) {
	Vector<T> temp(v);
	return (temp /= num);
}
template<class T>
Vector<T> operator*=(const Vector<T> & v,const Matrix<T>& m){


    Vector<T> temp(m.m_colum);
    for (int i = 0; i < m.m_colum; ++i) {
        for (int j = 0; j < m.m_row; ++j) {

                temp.v_array[i] += (v.v_array[j] * m.m_array[j][i]);

        }
    }
    return temp;

}


template <class T>
Vector<T> operator*(const Vector<T>& v1, const Matrix<T>& m2)
{
	if(v1.m_size==m2.m_row)
	{
    Vector<T> temp(v1);
    return (temp *= m2);
	}
	else
	{
		cout<<"Dimension does not match !!!";
		return 0;
	}
}


#endif /* VECTOR_H_ */
