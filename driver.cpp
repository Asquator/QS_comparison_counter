/*
The main driver that operates the quicksort efficiency analysis
*/

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
void run_counting_algo(decltype(quicksort_regular) *);

//calculates factorial of a number
constexpr unsigned long long factorial(unsigned int n) {
    return n == 1 ? 1 : (n * factorial(n-1));
}

static int N; //array size
static double quotient; //quotient of best/worst cases, a.k.a the "a parameter"

void fill_id_perm(vector<int>&);

int main(){
    //get parameters from the standard input
    void get_parameters();
    get_parameters();

    unsigned long long results_N = factorial(N);

    double avg_best1, avg_worst1, avg_total1,
            avg_best2, avg_worst2, avg_total2;

    //initializing the counter and running algorithms
    init_counter(results_N, quotient);
    run_counting_algo(quicksort_regular);
    avg_best1 = get_avg_best();
    avg_worst1 = get_avg_worst();
    avg_total1 = get_avg_total();

    init_counter(results_N, quotient);
    run_counting_algo(quicksort_medof3);
    avg_best2 = get_avg_best();
    avg_worst2 = get_avg_worst();
    avg_total2 = get_avg_total();

    //printing the results
    std::cout << "First algorithm: " << std::endl <<
    "Average of " << quotient << " worst cases: " << avg_worst1 << std::endl <<
    "Average of " << quotient << " best cases: " << avg_best1 << std::endl <<
    "Total average: " << avg_total1 << std::endl;

    std::cout << "Second algorithm: " << std::endl <<
    "Average of " << quotient << " worst cases: " << avg_worst2 << std::endl <<
    "Average of " << quotient << " best cases: " << avg_best2 << std::endl <<
    "Total average: " << avg_total2 << std::endl;
}

void get_parameters(){
    std::cout << "Insert the array length, a.k.a the \"n\" parameter: ";
    std::cin >> N;
    std::cout << "Insert the quotient of best/worst cases to be stored, a.k.a the \"a\" parameter: ";
    std::cin >> quotient;
    std::cin.get();
}

void display_perm(const vector<int>& a);

//runs an algorithm that is supposed to use the counter interface
void run_counting_algo(decltype(quicksort_regular) *sort_algorithm){
    vector<int> perm(N);
    vector<int> arr(N);

    //initializing the random seed
    srand(time(0));

    //starting from the identity permutation
    fill_id_perm(perm);

    do{
        //running through all permutations, performing the sort and advancing the counter
        arr = perm;
        sort_algorithm(arr);
        display_perm(perm);
        next_result_counter();
    } while(gen_next_permutation(perm));
}

void display_perm(const vector<int>& a){
    std::cout << "Permutation: [ ";
        print_arr(a);
        std::cout << "] comparisons: " << get_current_counter() << std::endl;
}
