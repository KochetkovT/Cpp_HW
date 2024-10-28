/**
 Сортирует массив по заданному алгоритму 
 @param n -- размер массива
 @param array -- массив (сколько звездочек насыпать в тип решайте сами)
 */

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

double get_time(){
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

using namespace std;

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *larr = new int[n1];
    int *rarr = new int[n2];

    for (int i = 0; i < n1; ++i){
        larr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; ++j){
        rarr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (larr[i] <= rarr[j]) {
            arr[k] = larr[i];
            ++i;
        } else {
            arr[k] = rarr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = larr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rarr[j];
        ++j;
        ++k;
    }

    delete[] larr;
    delete[] rarr;
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void my_merge_sort(int n, int * array){
    mergeSort(array, 0, n-1);
}

void heapify(int* arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void my_heap_sort(int n, int* array){
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(array, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}


int main() {
    int *arr = new int[]{12, 11, 13, 5, 6, 7};
    int n = 6;

    my_heap_sort(n, arr);
    printArray(arr, n);

    delete[] arr;
    arr = new int[]{1, 8, 32, 91, 16, 75};
    my_merge_sort(n, arr);
    printArray(arr, n);

    // ******************* Asymptotic check ***************************************

    double start = 0, finish = 0;
    int nstart = 10000, nfinish = 500000, nstep = 10000;

    cout.precision(6);

    std::ofstream out;
    out.open("heap.txt", ios::in | ios::out);
    out.clear(); // открываем файл для записи

    for (int n = nstart; n <= nfinish; n += nstep) {
        int *array = new int[n];
        for (int i = n; i > 0; i--) {
            array[n-i] = rand() % 10000;
        }

        start = get_time();
        my_heap_sort(n, array);
        finish = get_time();


        if (out.is_open())
        {
            out << finish - start << " " <<  n << std::endl;
        }


        cout << finish - start << "\n";
        delete [] array;
    }
    out.close();

    out.open("merge.txt", ios::in | ios::out);
    out.clear(); // открываем файл для записи

    for (int n = nstart; n <= nfinish; n += nstep) {
        int *array = new int[n];
        for (int i = n; i > 0; i--) {
            array[n-i] = rand() % 10000;
        }

        start = get_time();
        my_merge_sort(n, array);
        finish = get_time();


        if (out.is_open())
        {
            out << finish - start << " " <<  n << std::endl;
        }


        cout << finish - start << "\n";
        delete [] array;
    }
    out.close();
}



