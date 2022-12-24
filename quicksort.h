#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

#include "counter.h"

void quicksort_regular(std::vector<int>&);
void quicksort_medof3(std::vector<int>&);
int partition_custom(std::vector<int>& a, int l, int r, int pivot, bool count = false);

#endif
