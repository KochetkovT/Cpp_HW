#include <iostream>
#include <random>
#include <cmath>

#include "matrix.hpp"
#include "subvector.hpp"

int main()
{
	// 	Matrix<double> m1(3, 3);
	// 	m1(0, 0) = 1;
	// 	m1(0, 1) = 2;
	// 	m1(0, 2) = 3;
	// 	m1(1, 0) = -5;
	// 	m1(1, 1) = 1;
	// 	m1(1, 2) = 4;
	// 	m1(2, 0) = 5;
	// 	m1(2, 1) = 6;
	// 	m1(2, 2) = 0;

	// 	cout << "Determinant of m1: " << m1.determinant() << endl;
	// 	cout << m1 << endl;
	// 	cout << m1.transpose();

	std::cout << Matrix<double>::getSpecificDeterminant(200, 800).determinant() << std::endl;
	// 	cout << Matrix<double>::getSpecificDeterminant(100, -100).determinant() << endl;
	// 	cout << Matrix<double>::getSpecificDeterminant(50, 13).determinant() << endl;
}