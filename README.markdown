An algorithm for the weighted median
------------------------------------

### The weighted median problem

Given a length `n` array of values `a`, and an associated length `n` array of non-negative
weights `w`, compute a solution `c` to the following minimisation problem:

    \min_{c \in \mathbb{R}} \sum_{i=1}^n w_i * |a_i - c|

In the special case where all the weights `w_1, ..., w_n` agree and are strictly positive,
this reduces to the problem for the unweighted median.

### Wait, why?

This might be useful in e.g. machine learning applications where you wish to use the
L1 norm for your loss function and also want to assign non-uniform weights to your
training examples.

### Code

This weighted median implementation is written in C++ and makes use of the STL.
To use it, call `weighted_heap_select` as declared in `heap_select.h`:

    double weighted_heap_select(double *a, double *w, long n, double balance);

The first three arguments are assumed to be the length n array a of values,
the length n array w of non-negative weights, and n. The last argument should
be set to zero.

### Test

A simple test harness is provided in `test_lib.py`. The test code constructs
some random weighted median test problems and compares the running time and
output of the C++ code against directly solving the associated minimisation
problems using numerical optimisation. This test code depends upon Python,
Numpy and SciPy.

Running `make` in the top level directory will build the C++ code as a shared
library and then test it via the test harness.

### License

BSD. See `LICENSE.txt`

### References:

There's no claim to any algorithmic originality here - this is merely an
implementation of what has been known in the literature for some time, e.g.:

1.  Bleich & Overton : "A linear time algorithm for the weighted median problem". [pdf version of paper at us.archive.org](http://ia600304.us.archive.org/22/items/lineartimealgori00blei/lineartimealgori00blei.pdf)
2.  Cormen, Leiserson, Rivest, Stein : "Introduction to algorithms"

