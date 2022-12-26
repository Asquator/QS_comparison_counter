#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>

void inc_comp_counter(int);
void next_result_counter();
int get_current_counter();
void reset_comp_counter();
void init_counter(size_t, double quotient);

double get_avg_best();
double get_avg_worst();
double get_avg_total();

#endif
