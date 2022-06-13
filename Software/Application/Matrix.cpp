/*
 * Matrix.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#include <stdexcept>
#include "Matrix.h"

#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Matrix::Matrix(int rows, int cols) : m_row(rows), m_colum(cols)
{
	allocSpace();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] = 0;
        }
    }
}

Matrix::Matrix() : m_row(1), m_colum(1)
{
    allocSpace();
    m_array[0][0] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < m_row; ++i) {
        delete[] m_array[i];
    }
    delete[] m_array;
}

Matrix::Matrix(const Matrix& m) : m_row(m.m_row), m_colum(m.m_colum)
{
	allocSpace();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] = m.m_array[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m)
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
            m_array[i][j] = m.m_array[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] += m.m_array[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] -= m.m_array[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
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

Matrix& Matrix::operator*=(double num)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] *= num;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(double num)
{
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_colum; ++j) {
            m_array[i][j] /= num;
        }
    }
    return *this;
}



void Matrix::allocSpace()
{
    m_array = new double*[m_row];
    for (int i = 0; i < m_row; ++i) {
        m_array[i] = new double[m_colum];
    }
}

Matrix& Matrix::operator =(int *array) {

int k=0;

	    for (int i = 0; i < m_row; ++i) {
	        for (int j = 0; j < m_colum; ++j) {

	            m_array[i][j] = array[k++];
	        }
	}
	    return *this;
}



Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}

Matrix operator/(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp /= num);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.m_row; ++i) {
        os << m.m_array[i][0];
        for (int j = 1; j < m.m_colum; ++j) {
            os << " " << m.m_array[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.m_row; ++i) {
        for (int j = 0; j < m.m_colum; ++j) {
            is >> m.m_array[i][j];
        }
    }
    return is;
}


