#include <iostream>

using namespace std;

template <typename T>
class subvector
{
	T *mas;
	unsigned int top;
	unsigned int capacity;

	void copy(T *oldm)
	{
		if (oldm != nullptr)
		{
			for (unsigned int i = 0; i < top; ++i)
			{
				mas[i] = oldm[i];
			}
		}
	}

public:
	// Конструктор по умолчанию
	subvector() : mas(nullptr), top(0), capacity(0) {}

	// Параметризованный конструктор
	subvector(unsigned n, T value = T()) : top(n), capacity(2 * n)
	{
		mas = new T[capacity];
		for (unsigned int i = 0; i < top; i++)
		{
			mas[i] = value;
		}
	}

	// Деструктор
	~subvector()
	{
		delete[] mas;
	}

	// Конструктор копирования
	subvector(const subvector<T> &rhs)
	{
		top = rhs.top;
		capacity = rhs.capacity;
		mas = new T[capacity];
		copy(rhs.mas);
	}

	// Оператор присваивания копированием
	subvector &operator=(const subvector<T> &rhs)
	{
		if (this != &rhs)
		{
			delete[] mas;
			top = rhs.top;
			capacity = rhs.capacity;
			mas = new T[capacity];
			copy(rhs.mas);
		}
		return *this;
	}

	// Конструктор перемещения
	subvector(subvector<T> &&rhs)
	{
		mas = rhs.mas;
		top = rhs.top;
		capacity = rhs.capacity;
		rhs.mas = nullptr;
		rhs.top = 0;
		rhs.capacity = 0;
	}

	// Оператор присваивания перемещением
	subvector &operator=(subvector<T> &&rhs)
	{
		if (this != &rhs)
		{
			delete[] mas;
			mas = rhs.mas;
			top = rhs.top;
			capacity = rhs.capacity;
			rhs.mas = nullptr;
			rhs.top = 0;
			rhs.capacity = 0;
		}
		return *this;
	}

	T &operator[](unsigned int i)
	{
		if (i < top)
		{
			return mas[i];
		}
		else
		{
			return mas[top - 1];
		}
	}

	T operator[](unsigned int i) const
	{
		if (i < top)
		{
			return mas[i];
		}
		else
		{
			return mas[top - 1];
		}
	}

	bool push_back(const T &d)
	{
		if (top == capacity)
		{
			if (capacity != 0)
				capacity *= 2;
			else
				capacity = 1;
			T *oldv = mas;
			mas = new T[capacity];
			copy(oldv);
			delete[] oldv;
		}
		top += 1;
		mas[top - 1] = d;
		return true;
	} // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости

	T pop_back()
	{
		if (top == 0)
			return T();
		else
		{
			T d = mas[top - 1];
			top -= 1;
			return d;
		}
	} // удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть T{})

	bool resize(unsigned int new_capacity)
	{
		if (new_capacity > 0)
		{
			if (top > new_capacity)
			{
				top = new_capacity;
			}
			capacity = new_capacity;
			T *oldv = mas;
			mas = new T[capacity];
			copy(oldv);
			delete[] oldv;
			return true;
		}
		else
		{
			capacity = 0;
			top = 0;
			T *temp = mas;
			mas = nullptr;
			delete[] temp;
			return false;
		}
	} // увеличить емкость недовектора
	// (можно использовать и для уменьшения - тогда, в рамках данной реализации,
	// если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)

	void shrink_to_fit()
	{
		resize(top);
	} // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top

	void clear()
	{
		top = 0;
	} // очистить содержимое недовектора, занимаемое место при этом не меняется
};

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
		swap(rows_, cols_);
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
	// 	cout << m1 << endl;
	// 	cout << m1.transpose();

	// 	cout << Matrix<float>::getSpecificDeterminant(5, 81).determinant();
}