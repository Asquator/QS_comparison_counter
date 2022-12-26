#ifndef AUX_H
#define AUX_H

#include <vector>
#include <cstddef>
#include <ctime>
#include <cstdlib>

void print_arr(const std::vector<int>& a);
size_t linear_search(const std::vector<int>& a, size_t l, size_t r, int x);
void insertion_sort(std::vector<int>& arr, int l, int r);
void counting_sort(std::vector<int>& a, int lower, int upper);
void fill_arr(std::vector<int>& a, size_t l, size_t r, int val);
int min_in_arr(std::vector<int>& a);
int max_in_arr(std::vector<int>& a);
int random_range(int lower, int upper);

#endif
