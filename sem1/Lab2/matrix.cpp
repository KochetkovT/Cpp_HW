#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Matrix
{
	vector<T> data; // какой-то класс вектора: subvector или std::vector
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
		for (unsigned i = 0; i < rows; ++i)
		{
			for (unsigned j = 0; j < rows; ++j)
			{
				if (j != i)
				{
					T coef = T(rand() % 10);
					for (unsigned k = 0; k < cols; ++k)
					{
						matrix(i, k) += coef * matrix(j, k);
					}
				}
			}
		}
		return matrix;
	}

	// создание случайной матрицы с заданным детерминантом
	static Matrix getSpecificDeterminant(unsigned n, T determinant)
	{
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
					matrix(i, j) = T(rand() % 10);
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
				for (unsigned j = i + 1; j < rows_; ++j)
				{
					if (temp(j, i) != 0)
					{
						++cnt;
						for (unsigned k = 0; k < cols_; ++k)
						{
							swap(temp(i, k), temp(j, k));
						}
						break;
					}
				}
				if (!cnt)
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
		vector<T> transposed(cols_ * rows_);
		for (unsigned i = 0; i < rows_; ++i)
		{
			for (unsigned j = 0; j < cols_; ++j)
			{
				transposed[j * rows_ + i] = data[i * cols_ + j];
			}
		}
		data = move(transposed);
		swap(rows_, cols_);
		return *this;
	} // транспонирую себя

	Matrix transpose() const
	{
		vector<T> transposed(cols_ * rows_);
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

int main()
{
	Matrix<double> m1(3, 3);
	m1(0, 0) = 1;
	m1(0, 1) = 2;
	m1(0, 2) = 3;
	m1(1, 0) = -5;
	m1(1, 1) = 1;
	m1(1, 2) = 4;
	m1(2, 0) = 5;
	m1(2, 1) = 6;
	m1(2, 2) = 0;

	cout << "Determinant of m1: " << m1.determinant() << endl; 
	cout << m1 << endl;
	cout << m1.transpose();

	// 	cout << Matrix<float>::getSpecificDeterminant(5, 81).determinant();

}