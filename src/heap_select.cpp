#include "heap_select.h"

using namespace std;

double weighted_heap_select(double *a, double *w, long n, double balance) {
	assert(n > 0);
	priority_queue<pair<double, double> > q;
	for(long i = 0; i < n; ++i) {
		q.push(make_pair(a[i], w[i]));
	}
	double s = accumulate(w, w + n, 0.0);
	double t = -balance;
	assert(q.size());
	pair<double, double> x = q.top();
	while (s > t) {
		assert(q.size());
		x = q.top();
		q.pop();
		s -= x.second;
		t += x.second;
	}
	return x.first;
}

double heap_select(double *a, long n, long k) {
	k = (k >= n) ? (n - 1) : k;
	k = (k < 0) ? 0 : k;
	assert(0 <= k);
	assert(k < n);
	nth_element(a, a + k, a + n);
	return a[k];
}
