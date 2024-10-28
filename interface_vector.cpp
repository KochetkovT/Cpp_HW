#include <iostream>
using std::cout;

struct subvector {
     int* mas;
     unsigned int top; 
     unsigned int capacity;
};

void copy(int* oldm, int* newm, unsigned  int top){
    if(oldm != nullptr){
        for(unsigned int i = 0; i < top; ++i){
            *(newm + i) = *(oldm + i);
        }
        delete[] oldm;
    }
    // else delete oldm; // сомнительно
}

void init(subvector *qv){ // инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
}
void push_back(subvector *qv, int d){ // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
    auto& capacity = (qv->capacity);
    auto& top = (qv->top);
    if (top == capacity){
        if(capacity != 0) capacity *= 2;
        else capacity = 1;
        int* oldv = qv->mas;
        qv->mas = new int[capacity];
        copy(oldv, qv->mas, top);
    }
    top += 1;
    *(qv->mas + top - 1) = d;
}
int pop_back(subvector *qv) { // удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть ноль)
    auto& capacity = (qv->capacity);
    auto& top = (qv->top);
    if (top == 0) return 0;
    else{
        int d = *(qv->mas + top - 1);
        top -= 1;
        return d;
    }
}

void resize(subvector *qv, unsigned int new_capacity) { // увеличить емкость недовектора (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)
    if(new_capacity > 0) {
        auto &capacity = (qv->capacity);
        auto &top = (qv->top);
        if (top > new_capacity) top = new_capacity;
        capacity = new_capacity;
        int *oldv = qv->mas;
        qv->mas = new int[capacity];
        copy(oldv, qv->mas, top);
    }
    else{
        init(qv);
    }
}
void shrink_to_fit(subvector *qv){ // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top
    auto& top = (qv->top);
    resize(qv, top);
}

void clear(subvector *qv){ // очистить содержимое недовектора, занимаемое место при этом не меняется
    qv->top = 0;
}

void destructor(subvector *qv){ // очистить всю используемую память, инициализировать недовектор как пустой
    delete [] qv->mas;
    init(qv);
}

int main(){
    subvector* my_vector = new subvector;
    init(my_vector);
    push_back(my_vector, 10);
    push_back(my_vector, 2);
    cout << pop_back(my_vector) << "\n";
    cout << pop_back(my_vector) << "\n";
    cout << pop_back(my_vector) << "\n";
    cout << pop_back(my_vector) << "\n";
    cout << my_vector->top << " " << my_vector->capacity << "\n";

    clear(my_vector);
    cout << my_vector->top << " " << my_vector->capacity << "\n";
    shrink_to_fit(my_vector);
    cout << my_vector->top << " " << my_vector->capacity << "\n";

    if (my_vector->top)
    {
        cout  <<"--- !!! Falied clear !!! ---" ;
        return 0;
    }
    if (my_vector->capacity)
    {
        cout  <<"--- !!! Falied shrink_to_fit !!! ---";
        return 0;
    }
}