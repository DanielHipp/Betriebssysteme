#!/usr/bin/env python3

import sys
import os
from getopt import getopt
from getopt import GetoptError
import configparser
from decimal import *


def sqrt2(value, debug=False):
    assert type(value) == Decimal or type(value) == float or \
        type(value) == int or type(value) == long
    assert value >= 0

    getcontext().prec = prec

    value = Decimal(value)
    x = Decimal(start)
    if debug:
        print("Testing with value {}".format(str(value)))

    for i in range(loops):
        xpre = x

        if debug:
            print("Before iteration {:d}, x = {}".format(i, str(x)))

        x = (x + (value / x)) / Decimal(2)

        diff = abs(xpre - x)
        if diff < tolerance:
            break

    if debug:
        print("After {:d} iterations, x = {}".format(i + 1, str(x)))

    return x


def print_help():
    print("HELP")
    print("\t{} [OPTIONS]".format(sys.argv[0]))
    print("Possible options:")
    print("\t-h , --help")
    print("\t\tshows help")
    print("\t-d , --debug")
    print("\t\tprints debug inormation")
    print("\t-i , --input [number1],[number2],...")
    print("\t\tcalculates the square root of given numbers")
    print("\t-c , --config [FILE]")
    print("\t\tuses FILE as configuration")


def config(f):
    if not(os.path.exists(f)):
        print("File '" + f + "' does not exist!")
        print("Using default values.")

    global start
    global loops
    global tolerance

    conf = configparser.ConfigParser()
    conf.read(f)
    if "sqrt2" in conf:
        if "start" in conf["sqrt2"]:
            start = Decimal(conf["sqrt2"]["start"])
        if "loops" in conf["sqrt2"]:
            loops = int(conf["sqrt2"]["loops"])
        if "tolerance" in conf["sqrt2"]:
            tolerance = Decimal(conf["sqrt2"]["tolerance"])


def main():
    try:
        opts, args = getopt(sys.argv[1:], shortopts, longopts)
    except GetoptError:
        print("Illegal Arguments!")
        print("Try '-h' for help.")
        exit()

    if len(opts) == 0:
        print_help()
        exit()

    debug = False
    inputs = ""

    for i in range(len(opts)):
        opt, arg = opts[i]
        if opt == "-i" or opt == "--input":
            inputs = arg
        elif opt == "-h" or opt == "--help":
            print_help()
            exit()
        elif opt == "-d" or opt == "--debug":
            debug = True
        elif opt == "-c" or opt == "--config":
            config(str(arg))

    if len(inputs) == 0:
        print("No input given!")
        print("Try '-h' for help.")
        exit()

    # two pipes
    r1, w1 = os.pipe()
    r2, w2 = os.pipe()
    r1 = os.fdopen(r1, "r")
    w1 = os.fdopen(w1, "w")
    r2 = os.fdopen(r2, "r")
    w2 = os.fdopen(w2, "w")

    pid = os.fork()

    # child
    if pid == 0:
        w1.close()
        r2.close()

        values = r1.read()
        values = values.split(",")

        results = ""

        for val in values:
            try:
                res = str(sqrt2(Decimal(val), debug))
                results = "{}{}\n".format(results, res)
            except InvalidOperation:
                print("\"" + val + "\" was ignored.")

        w2.write(results)
        w2.flush()
        w2.close()
        r1.close()

    # parent
    elif pid > 0:
        r1.close()
        w2.close()

        w1.write(inputs)
        w1.flush()
        w1.close()

        results = r2.read()
        print(results)

        r2.close()


# default sqrt2 values
start = 1
loops = 100
tolerance = 1e-14

# precision, used for Decimal
prec = 25

shortopts = "hdi:c:"
longopts = ["help", "debug", "input=", "config="]

if __name__ == "__main__":
    main()
