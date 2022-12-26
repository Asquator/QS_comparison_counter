#include <vector>
#include <iostream>
#include <cstddef>
#include <climits>

#include "counter.h"
#include "quicksort.h"
#include "aux.h"
#include "select.h"

#define MIN_SELECT_RANGE 500000    //minimal value for the range between min and max values in best/worst arrys
                                    //from which select will be used instead of counting sort

static std::vector<int> best, worst;    //holds the best and worst cases results
static unsigned long long total_comp;   //holds the total comparisons number
static unsigned long long results_N;    //holds the number of permutations
static bool first_update = true;   //true until worst and best arrays are updated for the first time

size_t case_position;

//initializes counter
void init_counter(size_t n, double quotient){
    total_comp = 0;
    results_N = n;
    first_update = true;
    n = static_cast<size_t>(2 * n * quotient); //denotes sizes of best and worst (*2 to be able to store temp. values and use select algorithm)
    best.resize(n); // n best cases, then n temporary values
    worst.resize(n);  // n temporary values, then n worst cases
    case_position = 0;
}

//increase sthe current comparison counter
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

static void update_cases();

//advances the counter pointer (called each time new permutation is processed)
void next_result_counter(){
    ++case_position;
    size_t n = best.size();
    if(case_position >= n / 2){ //if the arrays are half-filled, process the best and worst cases
        case_position = 0;
        update_cases();
    }
    best[best.size() / 2 + case_position] = 0;
    worst[case_position] = 0;
}

static void update_cases(){
    std::cout << "Processing best and worst cases, this may take time" << std::endl;

    size_t min_best, max_best, min_worst, max_worst;
    min_best = min_in_arr(best);
    max_best = max_in_arr(best);
    min_worst = min_in_arr(worst);
    max_worst = max_in_arr(worst);

    if(first_update){   //filling with dummy values during the first update only
        fill_arr(best, 0, best.size()/2 - 1, max_best); //fill first n/2 best cases with the max value to be overwritten later
        fill_arr(worst, worst.size()/2, worst.size()-1, min_worst);  //fill last n/2 worst cases with the min value to be overwritten later
        first_update = false;
    }

    if(max_best - min_best > MIN_SELECT_RANGE)  //select and partition around the median
         select_randomized(best, 0, best.size()-1, best.size()/2);

    else     //counting sort is preferred for arrays with many identical numbers in a small range
        counting_sort(best, min_best, max_best);

    if(max_worst - min_worst > MIN_SELECT_RANGE)
         select_randomized(worst, 0, worst.size()-1, worst.size()/2);

    else
        counting_sort(worst, min_worst, max_worst);
}


//functions to get best/worst cases average

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


