/*
 * Matrix.h
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
class Matrix{
public:
	Matrix(int, int);
	Matrix();
	~Matrix();
	Matrix(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator=(int *array);

	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);

	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::istream& operator>>(std::istream&, Matrix&);
	int m_row, m_colum;
	double **m_array;
	void allocSpace();
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif /* MATRIX_H_ */
