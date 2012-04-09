#ifndef PARTITION_H
#define PARTITION_H

void partition(double *a, double x, long n, long & low,
	long & high);

void weighted_partition(double *a, double *w, double x, long n,
	long & low, long & high);

#endif // PARTITION_H
