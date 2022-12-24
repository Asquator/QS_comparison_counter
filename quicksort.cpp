#include <iostream>
#include <vector>

#include "quicksort.h"
#include "counter.h"
#include "aux.h"

using std::vector;

static void qs_regular(vector<int>&, int l, int r);
static void qs_medof3(vector<int>&, int l, int r);
void reverse(vector<int>&, int l, int r);

void quicksort_regular(vector<int>& a){
    qs_regular(a, 0, a.size() - 1);
}

void quicksort_medof3(vector<int>& a){
    qs_medof3(a, 0, a.size() - 1);
}

static void qs_regular(vector<int>& a, int l, int r){
    int pivot;
    if(l >= r) return;
    pivot = partition_custom(a, l, r, r, true);
    qs_regular(a, l, pivot-1);
    qs_regular(a, pivot+1, r);
}

static int pivot_medof3(const vector<int>& a, int l, int r);
static void qs_medof3(vector<int>& a, int l, int r){
    int pivot;
    if(l >= r) return;
    pivot = pivot_medof3(a, l, r);
    pivot = partition_custom(a, l, r, pivot, true);
    qs_medof3(a, l, pivot-1);
    qs_medof3(a, pivot+1, r);
}

static int pivot_medof3(const vector<int>& a, int l, int r){
    int mid = (l+r)/2;
    inc_comp_counter(2); //two comparisons are made
    if(a[l] < a[mid])
        return a[mid] < a[r] ? mid : r;
    return a[l] < a[r] ? l : r;
}

/*
//partition_custom: divide elements in the array using the given pivot index
//if count is true, counts comparisons (counter should be initialized)
*/
int partition_custom(vector<int>& a, int l, int r, int pivot, bool count /*= false */){
    int i = l;
    std::swap(a[pivot], a[r]); //placing the pivot in the end
    for(int j = l; j < r; j++){
        if(count)
            inc_comp_counter(1);

        if(a[j] <= a[r])
            std::swap(a[i++], a[j]);
    }

    std::swap(a[i], a[r]);  //placing the pivot in its final position
    return i;
}


