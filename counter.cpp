#include <vector>
#include <iostream>
#include <cstddef>
#include <climits>

#include "counter.h"
#include "quicksort.h"
#include "aux.h"
#include "select.h"

static std::vector<int> best, worst;
static unsigned long long total_comp;
static unsigned long long results_N;

size_t case_position;

void init_counter(size_t n, double quotient){
    total_comp = 0;
    results_N = n;
    n = static_cast<size_t>(2 * n * quotient); //denotes sizes of best and worst (*2 to be able to store temp. values and use select algorithm)
    best.resize(n); // n best cases, then n temporary values
    fill_arr(best, 0, n/2 - 1, INT_MAX); //fill first n/2 best cases with infinity to be overwritten later

    worst.resize(n);  // n temporary values, then n worst cases
    fill_arr(worst, 0, n-1, 0);
    case_position = 0;
}

void inc_comp_counter(int n){
    //update both counters in temporary best and worst cases
    best[best.size() / 2 + case_position] += n;
    worst[case_position] += n;

    //update total sum
    total_comp += n;
}

int get_current_counter(){
    return worst[case_position];
}

void next_result_counter(){
    ++case_position;
    size_t n = best.size();
    if(case_position >= n / 2){
        case_position = 0;

        select_randomized(best, 0, n-1, n/2);
        select_randomized(worst, 0, n-1, n/2);
    }
    best[best.size() / 2 + case_position] = 0;
    worst[case_position] = 0;
}

double get_avg_best(){
    unsigned long sum = 0;
    size_t sz = best.size() / 2;
    for(size_t i = 0; i < sz; i++)  //sum from the beginning to a half
        sum += best[i];

    return (double)sum / sz;
}

double get_avg_worst(){
    unsigned long sum = 0;
    size_t sz = worst.size() / 2;
    for(size_t i = sz; i < worst.size(); i++)   //sum from a half to the end
        sum += worst[i];

    return (double)sum / sz;
}

double get_avg_total(){
    return (double) total_comp / results_N;
}


