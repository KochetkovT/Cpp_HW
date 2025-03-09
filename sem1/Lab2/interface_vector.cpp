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
     // конструктор
     subvector() : mas(nullptr), top(0), capacity(0) {};

     // деструктор
     ~subvector()
     {
          delete[] mas;
     }

     // конструктор копирования
     subvector(const subvector<T> &rhs)
     {
          top = rhs.top;
          capacity = rhs.capacity;
          mas = new T[capacity];
          copy(rhs.mas);
     }

     // оператор присваивания копированием
     subvector &operator=(const subvector<T> &rhs)
     {
          if (this != &rhs)
          {
               top = rhs.top;
               capacity = rhs.capacity;
               T *temp = mas;
               T *mas = new T[capacity];
               copy(rhs.mas);
               delete[] temp;
          }
          return *this;
     }

     // конструктор перемещенея
     subvector(subvector<T> &&rhs)
     {
          mas = rhs.mas;
          top = rhs.top;
          capacity = rhs.capacity;
          rhs.mas = nullptr;
          rhs.top = 0;
          rhs.capacity = 0;
     }

     // оператор присваивания перемещением
     subvector &operator=(subvector<T> &&rhs)
     {
          if (this != &rhs)
          {
               T *temp = mas;
               unsigned int tmp_top = top;
               unsigned int tmp_cap = capacity;
               mas = rhs.mas;
               top = rhs.top;
               capacity = rhs.capacity;
               rhs.mas = temp;
               rhs.top = tmp_top;
               rhs.capacity = tmp_cap;
          }
          return *this;
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

int main()
{
     subvector<int> x;
     x.push_back(5);
     x.push_back(4);
     cout << x.pop_back() << endl;

     subvector<int> y;

     y.push_back(50);
     y.push_back(40);
     y.push_back(10);
     cout << y.pop_back() << endl;
     y = move(x);
     cout << y.pop_back() << endl;
}
