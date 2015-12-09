from libc.math cimport sqrt
from libc.math cimport fabs

# default sqrt2 values
cdef double start = 1
cdef loops = 100
cdef double tolerance = 1e-14


def sqrtm(double x):
    return sqrt(x)

def sqrt2(double value):
    cdef int i
    cdef double x = start
    for i in range(loops):
        xpre = x

        x = (x + (value / x)) / 2

        diff = fabs(xpre - x)
        if diff < tolerance:
            break
    return x
