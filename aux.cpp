#include <iostream>
#include "aux.h"
#include <climits>

//aux.cpp: auxiliary array functions

using std::vector;

int random_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

//print integer array
void print_arr(const vector<int>& a){
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
}

void fill_arr(vector<int>& a, size_t l, size_t r, int val){
    for(size_t i = l; i <= r; i++)
        a[i] = val;
}

//simple linear search in an array of integers
size_t linear_search(const vector<int>& a, size_t l, size_t r, int x){
    for (size_t i = l; i <= r; ++i) {
        if(a[i] == x)   return i;
    }

    return INT_MAX;
}

//regular insertion sort on an array of integers
void insertion_sort(vector<int>& arr, int l, int r){
    int i, j, key;
    for (i = l + 1; i <= r; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= l && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
