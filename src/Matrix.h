/*
 * Matrix.h
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
template <class T>
class Matrix{
public:
	Matrix(int, int);
	Matrix();
	~Matrix();
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator=(T *array);

	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);
	template <class U>
	friend std::ostream& operator<<(std::ostream&, const Matrix<U>&);
	template <class U>
	friend std::istream& operator>>(std::istream&, Matrix<U>&);
	int m_row, m_colum;
	T **m_array;
	void allocSpace();
};
template <class T>
Matrix<T>::Matrix(int rows, int cols) : m_row(rows), m_colum(cols)
{
	allocSpace();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] = 0;
        }
    }
}
template <class T>
Matrix<T>::Matrix() : m_row(1), m_colum(1)
{
    allocSpace();
    m_array[0][0] =(T**) 0;
}
template <class T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < m_row; ++i) {
        delete[] m_array[i];
    }
    delete[] m_array;
}
template <class T>
Matrix<T>::Matrix(const Matrix& m) : m_row(m.m_row), m_colum(m.m_colum)
{
	allocSpace();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] = m.m_array[i][j];
        }
    }
}
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    if (this == &m) {
        return *this;
    }

    if (m_row != m.m_row || m_colum != m.m_colum) {
        for (int i = 0; i < m_row; ++i) {
            delete[] m_array[i];
        }
        delete[] m_array;

        m_row = m.m_row;
        m_colum = m.m_colum;
        allocSpace();
    }

    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] =m.m_array[i][j];
        }
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] += (T**)m.m_array[i][j];
        }
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] -= (T**)m.m_array[i][j];
        }
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m)
{

    Matrix temp(m_row, m.m_colum);
    for (int i = 0; i < temp.m_row; ++i) {
        for (int j = 0; j < temp.m_colum; ++j) {
            for (int k = 0; k < m_colum; ++k) {
                temp.m_array[i][j] += (m_array[i][k] * m.m_array[k][j]);
            }
        }
    }
    return (*this = temp);
}
template <class T>
Matrix<T>& Matrix<T>::operator*=(double num)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] *= num;
        }
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator/=(double num)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] /= num;
        }
    }
    return *this;
}


template <class T>
void Matrix<T>::allocSpace()
{
    m_array = new T*[m_row];
    for (int i = 0; i < m_row; ++i) {
        m_array[i] = new T[m_colum];
    }
}
template <class T>
Matrix<T>& Matrix<T>::operator =(T *array) {

int k=0;

	    for (int i = 0; i < m_row; ++i) {
	        for (int j = 0; j < m_colum; ++j) {

	            m_array[i][j] = array[k++];
	        }
	}
	    return *this;
}


template <class T>
Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp += m2);
}
template <class T>
Matrix<T> operator-(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp -= m2);
}
template <class T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp *= m2);
}
template <class T>
Matrix<T> operator*(const Matrix<T>& m, double num)
{
    Matrix<T> temp(m);
    return (temp *= num);
}
template <class T>
Matrix<T> operator*(double num, const Matrix<T>& m)
{
    return (m * num);
}
template <class T>
Matrix<T> operator/(const Matrix<T>& m, double num)
{
    Matrix<T> temp(m);
    return (temp /= num);
}
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
    for (int i = 0; i < m.m_row; ++i) {
        os << m.m_array[i][0];
        for (int j = 1; j < m.m_colum; ++j) {
            os << " " << m.m_array[i][j];
        }
        os << std::endl;
    }
    return os;
}
template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& m)
{
    for (int i = 0; i < m.m_row; ++i) {
        for (int j = 0; j < m.m_colum; ++j) {
            is >> m.m_array[i][j];
        }
    }
    return is;
}




#endif /* MATRIX_H_ */
