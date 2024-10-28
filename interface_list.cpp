#include <iostream>

using namespace std;

struct subforwardlist {
    int data;
    subforwardlist* next;
};

unsigned int size(subforwardlist  **sfl){ //определить размер недосписка
    unsigned int size = 0;
    cout << "size in" << "\n";
    if(*sfl != nullptr){
        ++size;
        for(auto i = *sfl; i->next != nullptr; i = i->next){
            ++size;
//            cout << (*sfl)->data << "\n";
        }
        cout << size << "\n";
        cout << "sizen" << "\n";
        return size;
    }
    else{
        cout << "size0" << "\n";
        return size;
    }
}

subforwardlist* where_ptr(subforwardlist **sfl, int where){
    auto ptr = *sfl;
    cout << where << "hi \n";
    if (where < 0){
        return *sfl;
    }
    for(unsigned int i = 0;i < where; ++i){
        ptr = ptr->next;
//        cout << (*sfl)->data << "\n";
    }
//    cout << ptr->data << '\n';
    return  ptr;
}



void init(subforwardlist **sfl){ //инициализация пустого недосписка
    *sfl = nullptr;
}

void push_forward(subforwardlist **sfl, int d){ //добавление элемента в начало недосписка
    subforwardlist* elem = new subforwardlist;
    elem->data = d;
    elem->next = *sfl;
    *sfl = elem;
}

int pop_forward(subforwardlist **sfl){ //удаление элемента из начала недосписка, если пустой - возвращать 0
    if (*sfl == nullptr){
        return 0;
    }
    subforwardlist* tmp = *sfl;
    int d = (*sfl)->data;
    *sfl = (*sfl)->next;
    delete tmp;
    return d;
}

void push_back(subforwardlist **sfl, int d){ //добавление элемента в конец недосписка
    subforwardlist* elem = new subforwardlist;
    elem->data = d;
    elem->next = nullptr;
    cout << "push_back in" << "\n";
    if(*sfl == nullptr){
        *sfl = elem;
        cout << "push_back out1" << "\n";
    }
    else{
        subforwardlist* last;
        last = where_ptr(sfl,static_cast <int> (size(sfl)) - 1);
        last->next = elem;
        cout << "push_back out2" << "\n";
    }
}

int pop_back(subforwardlist **sfl){ //удаление элемента с конца недосписка, если пустой - возвращать 0
    if (*sfl == nullptr){
        return 0;
    }
    subforwardlist* pre_last;
    pre_last = where_ptr(sfl, static_cast <int> (size(sfl)) - 2);
    cout << "pop" << "\n";
    cout << pre_last->data << "\n";
    if(pre_last->next != nullptr){
        int d = pre_last->next->data;
        delete pre_last->next;
        pre_last->next = nullptr;
        return d;
    }
    else{
        int d = pre_last->data;
        delete pre_last;
        *sfl = nullptr;
        return d;
    }
}

bool push_where(subforwardlist **sfl, unsigned int where, int d){ //добавление элемента с порядковым номером where
    unsigned int s = size(sfl);
    if(*sfl == nullptr){
        return false;
    }
    if(where == 0){
        push_forward(sfl, d);
        return true;
    }
    else if(where < 0 || where >= s){
        return false;
    }
    subforwardlist* elem = new subforwardlist;
    elem->data = d;
    subforwardlist* prev;
    prev = where_ptr(sfl, where - 1);
    elem->next = prev->next;
    prev->next = elem;
    return true;
}

int erase_where(subforwardlist **sfl, unsigned int where){ //удаление элемента с порядковым номером where, если пустой - возвращать 0
    if(*sfl == nullptr){
        return 0;
    }
    unsigned int s = size(sfl);
    if(where == 0){
        return pop_forward(sfl);
    }
    else if(where + 1 == s){
        return pop_back(sfl);
    }
    else if(where < 0 || where >= s){
        return 0;
    }
    subforwardlist* prev, *tmp;
    prev = where_ptr(sfl, where - 1);
    tmp = prev->next;
    prev->next = tmp->next;
    int d = tmp->data;
    delete tmp;
    return d;
}



void clear(subforwardlist  **sfl) { //очистить содержимое недосписка
    init(sfl);
}

int main(){
    subforwardlist* my_list = new subforwardlist;
    init(&my_list);
//    push_forward(&my_list, 1);
//    push_forward(&my_list, 2);
//    push_forward(&my_list, 3);
//    push_forward(&my_list, 4);
//    push_forward(&my_list, 5);
    push_back(&my_list, 123);
//    cout << my_list->data << "\n";
    cout << pop_back(&my_list) << "\n";
//    cout << pop_forward(&my_list) << "\n";

}