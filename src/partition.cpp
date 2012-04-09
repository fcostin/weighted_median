#include "partition.h"

void partition(double *a, double x, long n, long & low,
		long & high) {

	// Partition array a of length n about the value x.
	//
	// Permutes a in place and finds indices low, high such that:
	//		a[i] < x	for all 0 <= i < low
	//		a[i] == x	for all low <= i < high
	//		a[i] > x	for all high <= i < n
	//
	// Note that the resulting three subsets are necessarily disjoint and
	// cover a.

	double tmp;
	long i = 0, j = 0, k = n;
	while (j < k) {
		if (a[j] < x) {
			tmp = a[j]; a[j] = a[i]; a[i] = tmp;
			++i;
			++j;
		} else if (a[j] > x) {
			--k;
			tmp = a[j]; a[j] = a[k]; a[k] = tmp;
		} else {
			++j;
		}
	}
	low = i;
	high = j;
	return;
}

void weighted_partition(double *a, double *w, double x, long n,
		long & low, long & high) {

	// Partition array a of length n, with weights w, about the value x.
	// Identical to unweighted partition, except w is permuted along with a.

	double tmp;
	long i = 0, j = 0, k = n;
	while (j < k) {
		if (a[j] < x) {
			tmp = a[j]; a[j] = a[i]; a[i] = tmp;
			tmp = w[j]; w[j] = w[i]; w[i] = tmp;
			++i;
			++j;
		} else if (a[j] > x) {
			--k;
			tmp = a[j]; a[j] = a[k]; a[k] = tmp;
			tmp = w[j]; w[j] = w[k]; w[k] = tmp;
		} else {
			++j;
		}
	}
	low = i;
	high = j;
	return;
}
