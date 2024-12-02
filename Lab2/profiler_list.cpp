#include <iostream>
#include <random>
#include <chrono>

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

using list = subforwardlist<int>;
using std::cout;
using std::endl;
double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 1e6;
}
int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}
int main()
{
    unsigned int n = 10000;
    int *test_sequence = new int[n], sum_for_O3 = 0, test_sequence_sum = 0, ongoing_sum = 0,
        *push_sequence = new int[n],
        *pop_sequence = new int[n],
        *pop_push_sequence_eq = new int[n],
        *pop_push_sequence_push = new int[n],
        *pop_push_sequence_pushpush = new int[n],
        *four_ways_test = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);
    //----------- Initialization
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        test_sequence[i] = rand_uns(0, n - 1);
        test_sequence_sum += test_sequence[i];
        push_sequence[i] = rand_uns(0, n - 1);
        pop_sequence[i] = rand_uns(0, n - 1);
        pop_push_sequence_eq[i] = rand_uns(0, 1);
        pop_push_sequence_push[i] = rand_uns(0, 5);
        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
        four_ways_test[i] = rand_uns(0, 3);
    }

    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
    list sv{};
    //----------- Test 000 Straight push_back
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_back(test_sequence[i]);
    }
    finish = get_time();
    cout << "000 Straight push_back: \t\t\t\t" << finish - start << endl;
    total += finish - start;
    //----------- Test 001 Straight pop_forward
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (sv.pop_forward() != test_sequence[i])
        {
            cout << endl
                 << "--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();
    if (sv.size())
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    cout << "001 Straight pop_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;
    //----------- Test 002 Straight push_forward
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_forward(test_sequence[i]);
    }
    finish = get_time();
    cout << "002 Straight push_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;
    //----------- Test 003 Straight pop_back
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (sv.pop_back() != test_sequence[i])
        {
            cout << endl
                 << "--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();
    if (sv.size())
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    cout << "003 Straight pop_back: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;
    //----------- Test 004 Random push_where
    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_back(test_sequence[i]);
    }
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_where(push_sequence[i], test_sequence[i]);
    }
    finish = get_time();
    if (sv.size() != 2 * n)
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }
    ongoing_sum = 0;
    for (unsigned int i = 0; i < 2 * n; i++)
    {
        ongoing_sum += sv.pop_back();
    }
    if (sv.size())
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    if (ongoing_sum != 2 * test_sequence_sum)
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, sum incoherent !!! ---" << endl;
        return 0;
    }
    cout << "004 Random push_where: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;
    //----------- Test 005 Random erase_where
    for (unsigned int i = 0; i < 2 * n; i++)
    {
        sv.push_back(test_sequence[i % n]);
    }
    sum_for_O3 = 0;
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sum_for_O3 += sv.erase_where(pop_sequence[i]);
    }
    finish = get_time();
    if (sv.size() != n)
    {
        cout << endl
             << "--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }
    cout << "005 Random erase_where: \t\t\t\t" << finish - start << " \t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 006 Random pop/push back equal amount
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();
    sv = list{};
    if (sv.size())
        std::cout << "Move assign works wrongly!!!" << std::endl;
    cout << "006 Random pop/push back equal amount: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 007 Random pop/push back more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();
    sv = list{};
    cout << "007 Random pop/push back more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 008 Random pop/push back much more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();

    sv = list{};
    cout << "008 Random pop/push back much more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 009 Random pop/push forward equal amount
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();
    sv = list{};
    cout << "009 Random pop/push forward equal amount: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 010 Random pop/push forward more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();
    sv = list{};
    cout << "010 Random pop/push forward more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 011 Random pop/push forward much more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();
    sv = list{};
    cout << "011 Random pop/push forward much more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- Test 012 Random pop/push four ways
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (four_ways_test[i] == 0)
            sv.push_back(test_sequence[i]);
        else if (four_ways_test[i] == 1)
            sum_for_O3 += sv.pop_back();
        else if (four_ways_test[i] == 2)
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();
    sv = list{};
    cout << "012 Random pop/push four ways: \t\t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
    //----------- End of tests
    //
    cout << "-----------" << endl
         << "Alltests finished, total time: \t" << total << endl;
    delete[] test_sequence;
    delete[] pop_push_sequence_eq;
    delete[] pop_push_sequence_push;
    delete[] pop_push_sequence_pushpush;
    delete[] push_sequence,
        delete[] pop_sequence,
        delete[] four_ways_test;

    return 0;
}