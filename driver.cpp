#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "quicksort.h"
#include "counter.h"
#include "aux.h"
#include "select.h"

using std::vector;

int gen_next_permutation(vector<int>& a);
void run_counting_sort_algo(decltype(quicksort_regular) *);

/*factorial: calculate factorial of a number at compile time*/
constexpr unsigned long long factorial(unsigned int n) {
    return n == 1 ? 1 : (n * factorial(n-1));
}

constexpr int N = 10; /*array size*/
constexpr double quotient = 0.01; /*quotient of best/worst cases, a.k.a the "a parameter" */
constexpr unsigned long long results_N = /*15000*;*/ factorial(N);

void fill_id_perm(vector<int>&);

int main(){
    double avg_best1, avg_worst1, avg_total1,
            avg_best2, avg_worst2, avg_total2;

    init_counter(results_N, quotient);
    run_counting_sort_algo(quicksort_regular);
    avg_best1 = get_avg_best();
    avg_worst1 = get_avg_worst();
    avg_total1 = get_avg_total();

    init_counter(results_N, quotient);
    run_counting_sort_algo(quicksort_medof3);
    avg_best2 = get_avg_best();
    avg_worst2 = get_avg_worst();
    avg_total2 = get_avg_total();

    std::cout << "First algorithm: " << std::endl <<
    "Average of " << quotient << " worst cases: " << avg_worst1 << std::endl <<
    "Average of " << quotient << " best cases: " << avg_best1 << std::endl <<
    "Total average: " << avg_total1 << std::endl;

    std::cout << "Second algorithm: " << std::endl <<
    "Average of " << quotient << " worst cases: " << avg_worst2 << std::endl <<
    "Average of " << quotient << " best cases: " << avg_best2 << std::endl <<
    "Total average: " << avg_total2 << std::endl;
}
void fill_random_perm(vector<int>& a, int lower, int upper);
void display_perm(const vector<int>& a);
void run_counting_sort_algo(decltype(quicksort_regular) *sort_algorithm){
    vector<int> perm(N);
    vector<int> arr(N);

    srand(time(0));
    fill_id_perm(perm);
  //  int i = 0;
    do{
  //  fill_random_perm(perm, 1, 10000);
        arr = perm;
        sort_algorithm(arr);
        display_perm(perm);

        next_result_counter();
    } while(gen_next_permutation(perm) /*i++ < results_N*/);
}

void display_perm(const vector<int>& a){
    std::cout << "Permutation: [ ";
        print_arr(a);
        std::cout << "] comparisons: " << get_current_counter() << std::endl;
}
