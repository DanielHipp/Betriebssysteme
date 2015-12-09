#!/usr/bin/env python3

import math
import forksqrt
import cyforksqrt
import timeit


def fork_sqrt2():
    forksqrt.sqrt2(arg)


def math_sqrt():
    math.sqrt(arg)


def cyfork_sqrt2():
    cyforksqrt.sqrt2(arg)


def cyfork_sqrtm():
    cyforksqrt.sqrtm(arg)


def main():

    fork_sqrt2_time = timeit.timeit(stmt=fork_sqrt2, number=n)
    math_sqrt_time = timeit.timeit(stmt=math_sqrt, number=n)
    cyfork_sqrt2_time = timeit.timeit(stmt=cyfork_sqrt2, number=n)
    cyfork_sqrtm_time = timeit.timeit(stmt=cyfork_sqrtm, number=n)

    print("===== cyforksqrt.sqrtm({:g}) =====".format(arg))
    print("Result: {}".format(cyforksqrt.sqrtm(arg)))
    print("Execution Time: {} sec".format(cyfork_sqrtm_time))

    print("===== cyforksqrt.sqrt2({:g}) =====".format(arg))
    print("Result: {}".format(cyforksqrt.sqrt2(arg)))
    print("Execution Time: {} sec".format(cyfork_sqrt2_time))

    print("===== forksqrt.sqrt2({:g}) =====".format(arg))
    print("Result: {:.14f}".format(forksqrt.sqrt2(arg)))
    print("Execution Time: {} sec".format(fork_sqrt2_time))

    print("===== math.sqrt({:g}) =====".format(arg))
    print("Result: {}".format(math.sqrt(arg)))
    print("Execution Time: {} sec".format(math_sqrt_time))


arg = 5
n = 100000

if __name__ == "__main__":
    main()
