#include <iostream>
#include "aux.h"
#include <climits>

//aux.cpp: auxiliary array functions

using std::vector;

//get random number in given range including the edges
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

int max_in_arr(vector<int>& a){
    if(a.empty()) return INT_MIN;
    int max = a[0];
    for(size_t i = 1; i < a.size(); i++){
        if(a[i] > max) max = a[i];
    }
    return max;
}

int min_in_arr(vector<int>& a){
    if(a.empty()) return INT_MAX;
    int min = a[0];
    for(size_t i = 1; i < a.size(); i++){
        if(a[i] < min) min = a[i];
    }
    return min;
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

void counting_sort(vector<int>& a, int lower, int upper){
    vector<int> count(upper-lower+1), output(a.size());
    int i;
    for (i = 0; i < a.size(); i++)
        count[a[i] - lower]++;

    for (i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (i = a.size() - 1; i >= 0; i--) {
        output[count[a[i] - lower] - 1] = a[i];
        count[a[i] - lower]--;
    }

    for (size_t i = 0; i < a.size(); i++)
        a[i] = output[i];
}
