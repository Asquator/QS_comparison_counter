#include <algorithm>
#include <vector>
#include <cstddef>
#include "aux.h"

using std::vector;

static void reverse(vector<int>& a, int l, int r);

//fills the array with identity permutation
void fill_id_perm(vector<int>& a){
    for(size_t i = 0; i < a.size(); i++)
        a[i] = i+1;
}

//fills an array with a random permutation from a given range. isn't used in the main branch, added to future extension of the project
//which will check the algorithms on random long permutations
void fill_random_perm(vector<int>& a, int lower, int upper){
    for(size_t i = 0; i < a.size(); i++){
        a[i] = random_range(lower, upper);
    }
}

//simple permutation generator: generates all permutations in lexiographical order, starting at the identity permutation
//returns false iff the last permutation was filled
bool gen_next_permutation(vector<int>& a){
    int n = a.size(), i = n - 2, c;
    while(i >= 0 && a[i] > a[i+1])
        i--;

    if(i < 0) return false;
    c = i+1;
    for(int j = i + 2; j <= n - 1; j++)
        if(a[i] < a[j] && a[j] < a[c])
            c = j;

    std::swap(a[i], a[c]);
    reverse(a, i+1, n-1);
    return true;
}

//reverse the array from l to r
static void reverse(vector<int>& a, int l, int r){
    int li = l, ri = r;
    while(li < ri){
        std::swap(a[li], a[ri]);
        li++, ri--;
    }
}
