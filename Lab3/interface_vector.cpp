#include <iostream>
#include <stdexcept>
using namespace std;

class VectorExeption: public exception {
protected:
    const char * string;
public:
    VectorExeption(const char * value): exception(), string(value) {}
    const char* what() const override {
        return string;
    }
};

class CopyError: public VectorExeption {
public:
    CopyError(const char * string): VectorExeption(string) {}
    const char * what() const  override {
        cout << "Copy error" << endl;
        return string;
    }
};

class PopError: public VectorExeption {
public:
    PopError(const char * string): VectorExeption(string) {}
    const char * what() const  override {
        cout << "Pop error" << endl;
        return string;
    }
};

class PushError: public VectorExeption {
public:
    PushError(const char * string): VectorExeption(string) {}
    const char * what() const  override {
        cout << "Push error" << endl;
        return string;
    }
};

class ResizeError: public VectorExeption {
public:
    ResizeError(const char * string): VectorExeption(string) {}
    const char * what() const  override {
        cout << "Resize error" << endl;
        return string;
    }
};


template <typename T>
class subvector
{
     T *mas;
     unsigned int top;
     unsigned int capacity;

     // void copy(T *oldm)
     // {
     //      if (oldm != nullptr)
     //      {
     //           for (unsigned int i = 0; i < top; ++i)
     //           {
     //                mas[i] = oldm[i];
     //           }
     //      }
     // }

     T *copy(const T *source, unsigned int top, unsigned int capacity)
     {
          try
          {
              T *out = new T[capacity];
          try
          {
               for (int i = 0; i < top; ++i)
                    out[i] = source[i];
          }
          catch (...)
          {
               delete[] out;
               throw CopyError("Failed while copying elements");
          }
          return out;
          }
          catch(bad_alloc & e)
          {
              throw CopyError("Failed to allocate new memory");
          }
          
     }

     void swp(subvector<T> &rhs) noexcept
     {
          swap(mas, rhs.mas);
          swap(top, rhs.top);
          swap(capacity, rhs.capacity);
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
     subvector(const subvector<T> &rhs): mas(copy(rhs.mas, rhs.top, rhs.capacity)), top(rhs.top),
         capacity(rhs.capacity)
     {
     }

     // оператор присваивания копированием
     subvector &operator=(const subvector<T> &rhs)
     {
          if (this != &rhs)
          {
               subvector<T> tmp(rhs);
               swp(tmp);
               return *this;
          }
          return *this;
     }

     // конструктор перемещенея
     subvector(subvector<T> &&rhs) noexcept
     {
          mas = rhs.mas;
          top = rhs.top;
          capacity = rhs.capacity;
          rhs.mas = nullptr;
          rhs.top = 0;
          rhs.capacity = 0;
          // может быть тут можно как то написать  через swap и деволтный конструктор но я посчитал что лучше оставить
     }

     // оператор присваивания перемещением
     subvector &operator=(subvector<T> &&rhs) noexcept
     {
          if (this != &rhs)
          {
               swp(rhs);
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
               try
               {
                    T *tmp = copy(mas, top, capacity);
                    delete[] mas;
                    mas = tmp;
                    
               }
               catch(CopyError & e)
               {
                    throw PushError(e.what());
               }
               
               
          }
          top += 1;
          mas[top - 1] = d;
          return true;
     } // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости

     T pop_back()
     {
          if (top == 0)
               throw PopError("Failed to pop from empty vector");
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
               T *tmp;
               try
               {
                    tmp = copy(mas, top, capacity);
                    delete[] mas;
                    mas = tmp;
               }
               catch(CopyError & e)
               {
                    throw ResizeError(e.what());
               }
               
               
               return true;
          }
          else
          {
               capacity = 0;
               top = 0;
               delete[] mas;
               mas = nullptr;
               return false;
          }
     } // увеличить емкость недовектора
     // (можно использовать и для уменьшения - тогда, в рамках данной реализации,
     // если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)

     void shrink_to_fit()
     {
          resize(top);
     } // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top

     void clear() noexcept
     {
          top = 0;
     } // очистить содержимое недовектора, занимаемое место при этом не меняется
};

int main()
{
     subvector<int> x;

     try
     {
         x.pop_back();
     }
     catch(PopError & e)
     {
          cout << e.what() << endl;
     }
     
     
     try
     {
         x.resize(10000000);
     }
     catch(ResizeError & e)
     {
          cout << e.what() << endl;
     }
    
}
