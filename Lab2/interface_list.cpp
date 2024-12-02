// Чтобы сделать list более похожим на класс, давайте инкапсулировать указатель на начальный элемент

#include <iostream>
using namespace std;

template <typename T>
class subforwardlist
{

    struct Node
    {
        T data;
        Node *next;
        // сюда можете написать что угодно для вашего удобства, нет органичений по списку методов
    };

    Node *begin;
    Node *end; // (опционально !) можете хранить указатель на последний элемент

    Node *where_ptr(int where)
    {
        Node *ptr = begin;
        if (ptr != nullptr)
        {
            if (where < 0)
            {
                return begin;
            }
            for (unsigned int i = 0; i < where; ++i)
            {
                ptr = ptr->next;
            }
        }
        return ptr;
    }

    void del(Node *ptr)
    {
        if (ptr->next != nullptr)
        {
            del(ptr->next);
        }
        delete ptr;
    }

    void swap(subforwardlist<T> &rhs)
    {
        Node *tmp = begin;
        begin = rhs.begin;
        rhs.begin = tmp;
        tmp = end;
        end = rhs.end;
        rhs.end = tmp;
    }

    void shrink_to_fit(unsigned int length)
    {
        unsigned int sz = size();
        while (length > sz)
        {
            push_back(T());
            ++sz;
        }
        while (length < sz)
        {
            pop_back();
            --sz;
        }
    }

public:
    T get_data(unsigned int where) const
    {
        if (begin == nullptr)
        {
            return T();
        }
        else
        {
            int cnt = 0;
            Node *i = begin;
            while (cnt != where and i != end)
            {
                cnt++;
                i = i->next;
            }
            if (cnt == where)
            {
                return i->data;
            }
            else
            {
                return T();
            }
        }
    }

    // Node* get_begin(){
    //     return begin;
    // }

    //  Node* get_end(){
    //     return end;
    // }

    // конструктор
    subforwardlist() : begin(nullptr), end(nullptr) {}

    // деструктор
    ~subforwardlist()
    {
        if (begin != nullptr)
        {
            del(begin);
        }
    }

    // конструктор копирования
    subforwardlist(const subforwardlist<T> &rhs)
    {
        begin = nullptr;
        end = nullptr;
        unsigned int size = rhs.size();
        for (int i = 0; i < size; i++)
        {
            push_back(rhs.get_data(i));
        }
        Node *sfl = begin;
        for (unsigned int i = 0; i < size; ++i)
        {
            sfl = sfl->next;
        }
        end = sfl;
    }

    // оператор присваивания копированием
    subforwardlist &operator=(const subforwardlist<T> &rhs)
    {
        if (this != &rhs)
        {
            unsigned int sz = rhs.size();
            shrink_to_fit(sz);
            Node *sfl = begin;
            Node *tmp = rhs.begin;
            for (unsigned int i = 0; i < sz; ++i)
            {
                sfl->data = tmp->data;
                sfl = sfl->next;
                tmp = tmp->next;
            }
        }
        return *this;
    }

    // конструктор перемещенея
    subforwardlist(subforwardlist<T> &&rhs)
    {
        begin = rhs.begin;
        end = rhs.end;
        rhs.begin = nullptr;
        rhs.end = nullptr;
    }

    // оператор присваивания перемещением
    subforwardlist &operator=(subforwardlist<T> &&rhs)
    {
        if (this != &rhs)
        {
            swap(rhs);
        }
        return *this;
    }

    unsigned int size()
    {
        unsigned int size = 0;
        if (begin != nullptr)
        {
            ++size;
            for (auto i = begin; i->next != nullptr; i = i->next)
            {
                ++size;
            }
        }
        return size;
    } // определить размер недосписка

    void push_back(const T &data)
    {
        Node *elem = new Node;
        elem->data = data;
        elem->next = nullptr;
        if (begin == nullptr)
        {
            begin = elem;
            end = elem;
        }
        else
        {
            end->next = elem;
            end = elem;
        }
    } // добавление элемента в конец
    T pop_back()
    {
        T d;
        if (begin == nullptr)
        {
            return T();
        }
        else if (size() == 1)
        {
            d = pop_forward();
        }
        else
        {
            Node *pre_last;
            pre_last = where_ptr(size() - 2);
            d = end->data;
            delete end;
            end = pre_last;
            end->next = nullptr;
        }
        return d;
    } // удаление элемента с конца (если пустой -- возвращать T{} (default конструирование объекта типа T))

    void push_forward(const T &data)
    {
        Node *elem = new Node;
        elem->data = data;
        elem->next = begin;

        if (begin == nullptr)
        {
            begin = elem;
            end = elem;
        }
        else
        {
            begin = elem;
        }
    } // добавление элемента в начало недосписка

    T pop_forward()
    {
        if (begin == nullptr)
        {
            return T();
        }
        Node *tmp = begin;
        T d = begin->data;
        if (begin == end)
        {
            begin = nullptr;
            end = nullptr;
        }
        else
        {
            begin = begin->next;
        }
        delete tmp;
        return d;
    } // удаление элемента из начала недосписка (если пустой -- возвращать T{} (default конструирование объекта типа T))

    void push_where(unsigned int where, const T &data)
    {
        unsigned int s = size();
        if (begin != nullptr)
        {
            if (where == 0)
            {
                push_forward(data);
            }
            else if (where == s - 1)
            {
                push_back(data);
            }
            else if (where > 0 || where < s - 1)
            {
                Node *elem = new Node;
                elem->data = data;
                Node *prev;
                prev = where_ptr(where - 1);
                elem->next = prev->next;
                prev->next = elem;
            }
        }
    } // добавление элемента с порядковым номером where

    T erase_where(unsigned int where)
    {
        if (begin == nullptr)
        {
            return T();
        }
        unsigned int s = size();
        if (where == 0)
        {
            return pop_forward();
        }
        else if (where + 1 == s)
        {
            return pop_back();
        }
        else if (where < 0 || where >= s)
        {
            return T();
        }
        Node *prev, *tmp;
        prev = where_ptr(where - 1);
        tmp = prev->next;
        prev->next = tmp->next;
        int d = tmp->data;
        delete tmp;
        return d;
    } // удаление элемента с порядковым номером where (если пустой -- возвращать T{} (default конструирование объекта типа T))
};

int main()
{
    subforwardlist<int> x;
    x.push_back(5);
    x.push_back(4);
    x.push_forward(3);

    cout << x.pop_forward() << endl;
    cout << x.pop_forward() << endl;
    cout << x.pop_forward() << endl;
    cout << x.pop_forward() << endl;
}