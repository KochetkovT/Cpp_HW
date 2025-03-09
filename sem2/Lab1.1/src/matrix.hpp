#ifndef HEADER_GUARD_MATRIX_HPP
#define HEADER_GUARD_MATRIX_HPP

#include <iostream>
#include <random>
#include <cmath>

#include "subvector.hpp"

template <typename T>
class Matrix
{
	subvector<T> data; // какой-то класс вектора: subvector или std::vector
	// предполагается, что хранение будет происходить в одном линейном массиве,
	// а не как с двойным указателем
	// предполагается, что матрица хранится построчно (Row-Major Ordering)
	unsigned rows_, cols_;

public:
	// 1) Конструирование

	// создание матрицы, заполненных value
	Matrix(unsigned rows, unsigned cols, T value = T())
		: data(rows * cols, value), rows_(rows), cols_(cols) {}

	// создание единичной матрицы
	static Matrix Identity(unsigned n)
	{
		Matrix matrix(n, n, T(0));
		for (unsigned i = 0; i < n; ++i)
		{
			matrix(i, i) = T(1);
		}
		return matrix;
	}

	static Matrix shuffle(Matrix<T> matrix)
	{
		unsigned rows = matrix.rows();
		unsigned cols = matrix.cols();
		std::random_device r;
		std::default_random_engine gen(r());
		std::uniform_real_distribution<double> coef_d(-1.0, 1.0);
		std::uniform_int_distribution<unsigned> num_d(0, rows - 1);
		unsigned rd = num_d(gen);
		for (unsigned i = 0; i < rows; ++i)
		{
			for (unsigned j = 0; j < rd; ++j)
			{
				unsigned w = num_d(gen);
				if (w != i)
				{
					T coef = T(coef_d(gen));
					for (unsigned k = 0; k < cols; ++k)
					{
						matrix(i, k) += coef * matrix(w, k);
					}
				}
			}
		}
		return matrix;
	}

	// создание случайной матрицы с заданным детерминантом
	static Matrix getSpecificDeterminant(unsigned n, T determinant)
	{
		std::random_device r;
		std::default_random_engine gen(r());
		
        std::uniform_real_distribution<double> el_d(std::max(double(determinant) / pow(10, n), 0.1), 1.0);
		
        Matrix matrix(n, n, T(0));

		for (unsigned i = 0; i < n; ++i)
		{
			for (unsigned j = 0; j < n; ++j)
			{
				if (i == j)
				{
					if (i == 0)
					{
						matrix(i, j) = determinant;
					}
					else
					{
						matrix(i, j) = T(1);
					}
				}
				else if (j > i)
				{
					matrix(i, j) = T(el_d(gen));
				}
			}
		}

		return shuffle(matrix);
	}

	// детерминант
	T determinant() const
	{
		Matrix<T> temp = *this;
		T det = T(1);
		unsigned cnt = 0;
		for (unsigned i = 0; i < rows_; ++i)
		{
			if (temp(i, i) == 0)
			{
				bool swapped = false;
				for (unsigned j = i + 1; j < rows_; ++j)
				{
					if (temp(j, i) != 0)
					{
						++cnt;
						for (unsigned k = 0; k < cols_; ++k)
						{
							std::swap(temp(i, k), temp(j, k));
						}
						swapped = true;
						break;
					}
				}
				if (!swapped)
					return T(0);
			}

			det *= temp(i, i);
			for (unsigned j = i + 1; j < rows_; ++j)
			{
				T coef = temp(j, i) / temp(i, i);
				for (unsigned k = i; k < cols_; ++k)
				{
					temp(j, k) -= coef * temp(i, k);
				}
			}
		}
		if (cnt % 2 == 0)
		{
			return det;
		}
		return -det;
	}

	// 2) Селекторы
	unsigned rows() const { return rows_; }

	unsigned cols() const { return cols_; }

	// 3) Методы для разминки и проверки работы вычисления детерминанта

	Matrix &transpose()
	{
		subvector<T> transposed(cols_ * rows_);
		for (unsigned i = 0; i < rows_; ++i)
		{
			for (unsigned j = 0; j < cols_; ++j)
			{
				transposed[j * rows_ + i] = data[i * cols_ + j];
			}
		}
		data = move(transposed);
		std::swap(rows_, cols_);
		return *this;
	} // транспонирую себя

	Matrix transpose() const
	{
		subvector<T> transposed(cols_ * rows_);
		for (unsigned i = 0; i < rows_; ++i)
		{
			for (unsigned j = 0; j < cols_; ++j)
			{
				transposed[j * rows_ + i] = data[i * cols_ + j];
			}
		}
		return transposed;
	} // копирую себя, транспонируют и возвращаю

	// Доступ к элементам матрицы
	T &operator()(unsigned row, unsigned col)
	{
		return data[row * cols_ + col];
	}

	T operator()(unsigned row, unsigned col) const
	{
		return data[row * cols_ + col];
	}
};

// вывод
template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix)
{
	unsigned rows = matrix.rows();
	unsigned cols = matrix.cols();
	for (size_t i = 0; i != rows; ++i)
	{
		for (size_t j = 0; j != cols; ++j)
		{
			if (j > 0)
			{
				out << "\t";
			}
			out << matrix(i, j);
		}
		out << "\n";
	}
	return out;
}

#endif // HEADER_GUARD_MATRIX_HPP