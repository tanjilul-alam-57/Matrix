/*
 * Matrix.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: mdalam
 */

#include <stdexcept>
#include "Matrix.h"

#define EPS 1e-10

using std::ostream;
using std::istream;
using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Matrix::Matrix(int rows, int cols) :
		m_row(rows), m_colum(cols) {
	allocSpace();
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] = 0;
		}
	}
}

Matrix::Matrix() :
		m_row(1), m_colum(1) {
	allocSpace();
	m_array[0][0] = 0;
}

Matrix::~Matrix() {
	for (int i = 0; i < m_row; ++i) {
		delete[] m_array[i];
	}
	delete[] m_array;
}

Matrix::Matrix(const Matrix& m) :
		m_row(m.m_row), m_colum(m.m_colum) {
	allocSpace();
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] = m.m_array[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& m) {
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

Matrix& Matrix::operator+=(const Matrix& m) {
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] += m.m_array[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] -= m.m_array[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {

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

Matrix& Matrix::operator*=(double num) {
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] *= num;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(double num) {
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			m_array[i][j] /= num;
		}
	}
	return *this;
}

Matrix Matrix::operator^(int num) {
	Matrix temp(*this);
	return expHelper(temp, num);
}

void Matrix::swapRows(int r1, int r2) {
	double *temp = m_array[r1];
	m_array[r1] = m_array[r2];
	m_array[r2] = temp;
}

Matrix Matrix::transpose() {
	Matrix ret(m_colum, m_row);
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_colum; ++j) {
			ret.m_array[j][i] = m_array[i][j];
		}
	}
	return ret;
}

/* STATIC CLASS FUNCTIONS
 ********************************/

Matrix Matrix::createIdentity(int size) {
	Matrix temp(size, size);
	for (int i = 0; i < temp.m_row; ++i) {
		for (int j = 0; j < temp.m_colum; ++j) {
			if (i == j) {
				temp.m_array[i][j] = 1;
			} else {
				temp.m_array[i][j] = 0;
			}
		}
	}
	return temp;
}

Matrix Matrix::solve(Matrix A, Matrix b) {
	// Gaussian elimination
	for (int i = 0; i < A.m_row; ++i) {
		if (A.m_array[i][i] == 0) {
			// pivot 0 - throw error
			throw domain_error(
					"Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again.");
		}
		for (int j = i + 1; j < A.m_row; ++j) {
			for (int k = i + 1; k < A.m_colum; ++k) {
				A.m_array[j][k] -= A.m_array[i][k]
						* (A.m_array[j][i] / A.m_array[i][i]);
				if (A.m_array[j][k] < EPS && A.m_array[j][k] > -1 * EPS)
					A.m_array[j][k] = 0;
			}
			b.m_array[j][0] -= b.m_array[i][0]
					* (A.m_array[j][i] / A.m_array[i][i]);
			if (A.m_array[j][0] < EPS && A.m_array[j][0] > -1 * EPS)
				A.m_array[j][0] = 0;
			A.m_array[j][i] = 0;
		}
	}

	// Back substitution
	Matrix x(b.m_row, 1);
	x.m_array[x.m_row - 1][0] = b.m_array[x.m_row - 1][0]
			/ A.m_array[x.m_row - 1][x.m_row - 1];
	if (x.m_array[x.m_row - 1][0] < EPS && x.m_array[x.m_row - 1][0] > -1 * EPS)
		x.m_array[x.m_row - 1][0] = 0;
	for (int i = x.m_row - 2; i >= 0; --i) {
		int sum = 0;
		for (int j = i + 1; j < x.m_row; ++j) {
			sum += A.m_array[i][j] * x.m_array[j][0];
		}
		x.m_array[i][0] = (b.m_array[i][0] - sum) / A.m_array[i][i];
		if (x.m_array[i][0] < EPS && x.m_array[i][0] > -1 * EPS)
			x.m_array[i][0] = 0;
	}

	return x;
}

Matrix Matrix::bandSolve(Matrix A, Matrix b, int k) {
	// optimized Gaussian elimination
	int bandsBelow = (k - 1) / 2;
	for (int i = 0; i < A.m_row; ++i) {
		if (A.m_array[i][i] == 0) {
			// pivot 0 - throw exception
			throw domain_error(
					"Error: the coefficient matrix has 0 as a pivot. Please fix the input and try again.");
		}
		for (int j = i + 1; j < A.m_row && j <= i + bandsBelow; ++j) {
			int k = i + 1;
			while (k < A.m_colum && A.m_array[j][k]) {
				A.m_array[j][k] -= A.m_array[i][k]
						* (A.m_array[j][i] / A.m_array[i][i]);
				k++;
			}
			b.m_array[j][0] -= b.m_array[i][0]
					* (A.m_array[j][i] / A.m_array[i][i]);
			A.m_array[j][i] = 0;
		}
	}

	// Back substitution
	Matrix x(b.m_row, 1);
	x.m_array[x.m_row - 1][0] = b.m_array[x.m_row - 1][0]
			/ A.m_array[x.m_row - 1][x.m_row - 1];
	for (int i = x.m_row - 2; i >= 0; --i) {
		int sum = 0;
		for (int j = i + 1; j < x.m_row; ++j) {
			sum += A.m_array[i][j] * x.m_array[j][0];
		}
		x.m_array[i][0] = (b.m_array[i][0] - sum) / A.m_array[i][i];
	}

	return x;
}

// functions on VECTORS
double Matrix::dotProduct(Matrix a, Matrix b) {
	double sum = 0;
	for (int i = 0; i < a.m_row; ++i) {
		sum += (a(i, 0) * b(i, 0));
	}
	return sum;
}

// functions on AUGMENTED matrices
Matrix Matrix::augment(Matrix A, Matrix B) {
	Matrix AB(A.m_row, A.m_colum + B.m_colum);
	for (int i = 0; i < AB.m_row; ++i) {
		for (int j = 0; j < AB.m_colum; ++j) {
			if (j < A.m_colum)
				AB(i, j) = A(i, j);
			else
				AB(i, j) = B(i, j - B.m_colum);
		}
	}
	return AB;
}

Matrix Matrix::gaussianEliminate() {
	Matrix Ab(*this);
	int rows = Ab.m_row;
	int cols = Ab.m_colum;
	int Acols = cols - 1;

	int i = 0; // row tracker
	int j = 0; // column tracker

	// iterate through the rows
	while (i < rows) {
		// find a pivot for the row
		bool pivot_found = false;
		while (j < Acols && !pivot_found) {
			if (Ab(i, j) != 0) { // pivot not equal to 0
				pivot_found = true;
			} else { // check for a possible swap
				int max_row = i;
				double max_val = 0;
				for (int k = i + 1; k < rows; ++k) {
					double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
					if (cur_abs > max_val) {
						max_row = k;
						max_val = cur_abs;
					}
				}
				if (max_row != i) {
					Ab.swapRows(max_row, i);
					pivot_found = true;
				} else {
					j++;
				}
			}
		}

		// perform elimination as normal if pivot was found
		if (pivot_found) {
			for (int t = i + 1; t < rows; ++t) {
				for (int s = j + 1; s < cols; ++s) {
					Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
					if (Ab(t, s) < EPS && Ab(t, s) > -1 * EPS)
						Ab(t, s) = 0;
				}
				Ab(t, j) = 0;
			}
		}

		i++;
		j++;
	}

	return Ab;
}

Matrix Matrix::rowReduceFromGaussian() {
	Matrix R(*this);
	int rows = R.m_row;
	int cols = R.m_colum;

	int i = rows - 1; // row tracker
	int j = cols - 2; // column tracker

	// iterate through every row
	while (i >= 0) {
		// find the pivot column
		int k = j - 1;
		while (k >= 0) {
			if (R(i, k) != 0)
				j = k;
			k--;
		}

		// zero out elements above pivots if pivot not 0
		if (R(i, j) != 0) {

			for (int t = i - 1; t >= 0; --t) {
				for (int s = 0; s < cols; ++s) {
					if (s != j) {
						R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
						if (R(t, s) < EPS && R(t, s) > -1 * EPS)
							R(t, s) = 0;
					}
				}
				R(t, j) = 0;
			}

			// divide row by pivot
			for (int k = j + 1; k < cols; ++k) {
				R(i, k) = R(i, k) / R(i, j);
				if (R(i, k) < EPS && R(i, k) > -1 * EPS)
					R(i, k) = 0;
			}
			R(i, j) = 1;

		}

		i--;
		j--;
	}

	return R;
}

void Matrix::readSolutionsFromRREF(ostream& os) {
	Matrix R(*this);

	// print number of solutions
	bool hasSolutions = true;
	bool doneSearching = false;
	int i = 0;
	while (!doneSearching && i < m_row) {
		bool allZeros = true;
		for (int j = 0; j < m_colum - 1; ++j) {
			if (R(i, j) != 0)
				allZeros = false;
		}
		if (allZeros && R(i, m_colum - 1) != 0) {
			hasSolutions = false;
			os << "NO SOLUTIONS" << endl << endl;
			doneSearching = true;
		} else if (allZeros && R(i, m_colum - 1) == 0) {
			os << "INFINITE SOLUTIONS" << endl << endl;
			doneSearching = true;
		} else if (m_row < m_colum - 1) {
			os << "INFINITE SOLUTIONS" << endl << endl;
			doneSearching = true;
		}
		i++;
	}
	if (!doneSearching)
		os << "UNIQUE SOLUTION" << endl << endl;

	// get solutions if they exist
	if (hasSolutions) {
		Matrix particular(m_colum - 1, 1);
		Matrix special(m_colum - 1, 1);

		for (int i = 0; i < m_row; ++i) {
			bool pivotFound = false;
			bool specialCreated = false;
			for (int j = 0; j < m_colum - 1; ++j) {
				if (R(i, j) != 0) {
					// if pivot variable, add b to particular
					if (!pivotFound) {
						pivotFound = true;
						particular(j, 0) = R(i, m_colum - 1);
					} else { // otherwise, add to special solution
						if (!specialCreated) {
							special = Matrix(m_colum - 1, 1);
							specialCreated = true;
						}
						special(j, 0) = -1 * R(i, j);
					}
				}
			}
			os << "Special solution:" << endl << special << endl;
		}
		os << "Particular solution:" << endl << particular << endl;
	}
}

Matrix Matrix::inverse() {
	Matrix I = Matrix::createIdentity(m_row);
	Matrix AI = Matrix::augment(*this, I);
	Matrix U = AI.gaussianEliminate();
	Matrix IAInverse = U.rowReduceFromGaussian();
	Matrix AInverse(m_row, m_colum);
	for (int i = 0; i < AInverse.m_row; ++i) {
		for (int j = 0; j < AInverse.m_colum; ++j) {
			AInverse(i, j) = IAInverse(i, j + m_colum);
		}
	}
	return AInverse;
}

/* PRIVATE HELPER FUNCTIONS
 ********************************/

void Matrix::allocSpace() {
	m_array = new double*[m_row];
	for (int i = 0; i < m_row; ++i) {
		m_array[i] = new double[m_colum];
	}
}

Matrix Matrix::expHelper(const Matrix& m, int num) {
	if (num == 0) {
		return createIdentity(m.m_row);
	} else if (num == 1) {
		return m;
	} else if (num % 2 == 0) {  // num is even
		return expHelper(m * m, num / 2);
	} else {                    // num is odd
		return m * expHelper(m * m, (num - 1) / 2);
	}
}

/* NON-MEMBER FUNCTIONS
 ********************************/

Matrix operator+(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp *= m2);
}

Matrix operator*(const Matrix& m, double num) {
	Matrix temp(m);
	return (temp *= num);
}

Matrix operator*(double num, const Matrix& m) {
	return (m * num);
}

Matrix operator/(const Matrix& m, double num) {
	Matrix temp(m);
	return (temp /= num);
}

ostream& operator<<(ostream& os, const Matrix& m) {
	for (int i = 0; i < m.m_row; ++i) {
		os << m.m_array[i][0];
		for (int j = 1; j < m.m_colum; ++j) {
			os << " " << m.m_array[i][j];
		}
		os << endl;
	}
	return os;
}

istream& operator>>(istream& is, Matrix& m) {
	for (int i = 0; i < m.m_row; ++i) {
		for (int j = 0; j < m.m_colum; ++j) {
			is >> m.m_array[i][j];
		}
	}
	return is;
}

