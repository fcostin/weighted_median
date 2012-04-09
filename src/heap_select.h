#ifndef HEAP_SELECT_H
#define HEAP_SELECT_H

#include <algorithm>
#include <queue>
#include <numeric>
#include <utility>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

double weighted_heap_select(double *a, double *w, long n, double balance);

double heap_select(double *a, long n, long k);

#ifdef __cplusplus
}
#endif

#endif //HEAP_SELECT_H
