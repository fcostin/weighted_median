#ifndef MEDIAN_H
#define MEDIAN_H

#include "heap_select.h"
#include "partition.h"
#include <string.h>
#include <numeric>
#include "assert.h"

#ifdef __cplusplus
extern "C" {
#endif

const long SELECT_SMALL_N = 128;
const long SELECT_BIN_SIZE = 7;

double weighted_select(double *a, double *w, long n, double balance);
double unweighted_select(double *a, long n, long k);

#ifdef __cplusplus
}
#endif

#endif // MEDIAN_H
