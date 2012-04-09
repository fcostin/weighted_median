"""
Test libwtmedian

libwtmedian provides an implementation of an algorithm to
compute the weighted median of an array of numbers with an
associated array of weights.

Compare performance and accuracy of src/libwtmedian.so against
a simpler implementation based on directly numerically solving the
associated minimisation problem for the weighted median using
scipy.optimize.fmin.
"""

import numpy
import ctypes
import time
import sys


def expensive_weighted_select(a, w):
    """
    explicitly solve minimisation problem for weighted median

    arguments:
        a : length n array of input values
        w : length n array of weights. must be non-negative
    returns:
        the weighted median (a scalar value)
    """
    import scipy.optimize
    a = numpy.asarray(a)
    w = numpy.asarray(w)
    assert numpy.all(w >= 0.0)

    def f(c):
        return numpy.sum(w * numpy.abs(a - c))

    c_0 = numpy.median(a)
    (c_opt, ) = scipy.optimize.fmin(f, c_0, disp = 0)
    return c_opt

def as_c_array(a):
    n = len(a)
    b = (ctypes.c_double * n)()
    b[:] = a[:]
    return b


def make_weighted_select(n):
    """
    interface to weighted_select function from libwtmedian.so
    """
    lib = ctypes.CDLL('src/libwtmedian.so')
    _weighted_select = lib.weighted_select
    _weighted_select.argtypes = [(ctypes.c_double * n),
            (ctypes.c_double * n), ctypes.c_long, ctypes.c_double]
    _weighted_select.restype = ctypes.c_double

    def weighted_select(a, w):
        n = len(a)
        balance = 0.0
        return _weighted_select(a, w, n, balance)
    return weighted_select

def main():
    numpy.seterr(all = 'raise')
    print('setup:')
    n = 200000

    weighted_select = make_weighted_select(n)

    methods = {
        'python_fmin' : (expensive_weighted_select, False),
        'libwtmedian' : (weighted_select, True),
    }
    method_names = sorted(methods)
    
    print('ok')
    n_runs = 20

    print('making problems:')
    problems = []
    for i in range(n_runs):
        print('\tproblem %d' % i)
        a = numpy.random.uniform(-1000.0, 1000.0, n)
        w = numpy.random.uniform(0.0, 1000.0, n)
        problems.append((a, w, as_c_array(a), as_c_array(w)))
    print('ok')
    
    results = {}
    for name in method_names:
        print('testing "%s"' % name)
        f, c_flag = methods[name]
        if c_flag:
            print('\t(using ctypes inputs)')
        t_0 = time.time()
        for (a, w, ca, cw) in problems:
            if c_flag:
                res = f(ca, cw)
            else:
                res = f(a, w)
            if name not in results:
                results[name] = [res]
            else:
                results[name].append(res)
        t_1 = time.time()
        delta_t = t_1 - t_0
        print('\tdelta_t = %f' % delta_t)

    print('checking result consistency:')
    tol = 1.0e-10
    for i in range(n_runs):
        prev_res = None
        for name in method_names:
            res = results[name][i]
            if prev_res is not None:
                assert numpy.abs(prev_res, res) < tol
                prev_res = res
    print('all methods agree within tolerance: %e' % tol)

if __name__ == '__main__':
    main()
