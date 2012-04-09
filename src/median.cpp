#include "median.h"

using namespace std;

double weighted_select(double *a, double *w, long n, double balance) {

	// use simpler algorithm for small n
	if (n < SELECT_SMALL_N) {
		return weighted_heap_select(a, w, n, balance);
	}

	// compute median of medians of 5 element blocks
	long n_medians = n / SELECT_BIN_SIZE + ((n % SELECT_BIN_SIZE) > 0);
	double *block = new double[SELECT_BIN_SIZE];
	double *medians = new double[n_medians];
	long j = 0;
	for (long i = 0; i < n; i += SELECT_BIN_SIZE) {
		long b = (SELECT_BIN_SIZE < (n - i)) ? SELECT_BIN_SIZE : (n - i);
		// copy block before in place partial sort to avoid
		// having to apply same permutation to block of w
		memcpy(block, a + i, b * sizeof(double));
		medians[j++] = heap_select(block, b, b/2);
	}
	double mm = unweighted_select(medians, n_medians, n_medians / 2);
	delete[] medians;
	delete[] block;

	// partition about median of medians mm
	long low, high;
	weighted_partition(a, w, mm, n, low, high);
	assert(0 <= low);
	assert(low <= high);
	assert(high <= n);
	assert((low < n) || (high < n));
	double w_lt = accumulate(w, w + low, 0.0);
	double w_eq = accumulate(w + low, w + high, 0.0);
	double w_gt = accumulate(w + high, w + n, 0.0);

	if ((w_lt + balance) >= (w_eq + w_gt)) {
		// too much mass in lower subset
		return weighted_select(a, w, low, balance - w_eq - w_gt);
	} else if ((w_lt + w_eq + balance) < w_gt) {
		// too much mass in upper subset
		return weighted_select(a + high, w + high, n - high, balance + w_lt + w_eq);
	} else {
		// mass balanced about 1 or more values equal to mm, so return mm
		return mm;
	}
}

double unweighted_select(double *a, long n, long k) {
	assert(0 <= k);
	assert(k <= n);

	// use simpler algorithm for small n
	if (n < SELECT_SMALL_N) {
		return heap_select(a, n, k);
	}

	// compute median of medians of 5 element blocks
	long n_medians = n / SELECT_BIN_SIZE + ((n % SELECT_BIN_SIZE) > 0);
	double *medians = new double[n_medians];
	long j = 0;
	for (long i = 0; i < n; i += SELECT_BIN_SIZE) {
		long b = (SELECT_BIN_SIZE < (n - i)) ? SELECT_BIN_SIZE : (n - i);
		assert(j < n_medians);
		assert(i + b <= n);
		assert(i + (b/2) < n);
		medians[j++] = heap_select(a + i, b, b/2);
	}
	double mm = unweighted_select(medians, n_medians, n_medians / 2);
	delete[] medians;

	// partition about median of medians mm
	long low, high;
	partition(a, mm, n, low, high);
	
	if (low >= k) {
		return unweighted_select(a, low, k);
	} else if (high >= k) {
		return mm;
	} else {
		return unweighted_select(a + high, n - high, k - high);
	}
}
