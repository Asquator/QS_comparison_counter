#include <climits>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "quicksort.h"
#include "aux.h"

using std::vector;

//sort_find_median: sort the array and return its median
static size_t sort_find_median(vector<int>& a, size_t l, size_t r){
    insertion_sort(a, l, r);
    return a[(r+l)/2];
}

int select_deter(vector<int>& arr, size_t l, size_t r, size_t k){
    // If k is smaller than number of elements in array
    if (k <= 0 || k > r - l + 1)
        throw std::runtime_error("Invalid order statistic");

    size_t n = r-l+1; // Number of elements in arr[l..r]
    size_t i;

    vector<int> medians((n+4)/5);   //array of medians

    for (i=0; i<n/5; i++)
        medians[i] = sort_find_median(arr, l+i*5, l+(i+1)*5-1);

    if (n%5 != 0) //For last group with less than 5 elements
    {
        medians[i] = sort_find_median(arr, l+i*5, l+i*5+n%5-1);
        ++i;
    }

    //find the median of medians and use at as a pivot in partition
    size_t med_of_med = (i == 1)? medians[0] : select_deter(medians, 0, i-1, (i+1)/2);
    size_t pivot = linear_search(arr, l, r, med_of_med);
    pivot = partition_custom(arr, l, r, pivot);

    // if position is same as k
    if (pivot-l == k-1)
        return arr[pivot];
    // recur for left
    if (pivot-l > k-1)
        return select_deter(arr, l, pivot-1, k);

    // recur for right
    return select_deter(arr, pivot+1, r, k-pivot+l-1);
}


int select_randomized(vector<int>& arr, size_t l, size_t r, size_t k){
     // If k is smaller than number of elements in array
    if (k <= 0 || k > r - l + 1)
        throw std::runtime_error("Invalid order statistic");

    if(l==r)
        return arr[l];

    int pivot = random_range(l, r);
    std::cout << "RANDOM: " << pivot << std::endl;
    pivot = partition_custom(arr, l, r, pivot);

     // if position is same as k
    if (pivot-l == k-1)
        return arr[pivot];

    //recur for left
    if (pivot-l > k-1)
        return select_randomized(arr, l, pivot-1, k);

    // recur for right
    return select_randomized(arr, pivot+1, r, k-pivot+l-1);

}
