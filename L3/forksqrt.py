#!/usr/bin/env python3

import sys
import os
import math
import time
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
    print("\t\tshow help")
    print("\t-d , --debug")
    print("\t\tprint debug inormation")
    print("\t-i , --input [number1],[number2],...")
    print("\t\tcalculate the square root of given numbers")
    print("\t-c , --config [FILE]")
    print("\t\tuse FILE as configuration")
    print("\t-f , --file [FILE]")
    print("\t\tuse FILE as input")
    print("\t-o , --ouput [FILE]")
    print("\t\tprint ouput into FILE")
    print("\t-p , --proc")
    print("\t\tuse 4 processes for more speed")
    print("\t-s , --size [SIZE]")
    print("\t\tset the fragment size to SIZE")


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


def get_input_from_file(name):
    inputs = []
    if not os.path.exists(name):
        print("'{}' does not exist.".format(name))
        return inputs
    with open(name) as f:
        for line in f:
            inputs.append(line.strip())
    return inputs


def calculate_sqrt_child_proc(r, w, debug=False):
    results = ""

    for values in r:
        if values == "":
            break

        values = values.split(",")

        for val in values:
            try:
                res = str(sqrt2(Decimal(val), debug))
                results = "{}{}\n".format(results, res)
            except InvalidOperation:
                print("'" + val.strip() + "' was ignored.")

    w.write(results)
    w.flush()
    w.close()
    r.close()


def get_pipes(n):
    child_to_parent_pipes = []
    parent_to_child_pipes = []
    for i in range(n):
        child_to_parent_pipes.append({})
        parent_to_child_pipes.append({})
        r1, w1 = os.pipe()
        r2, w2 = os.pipe()
        r1 = os.fdopen(r1, "r")
        w1 = os.fdopen(w1, "w")
        r2 = os.fdopen(r2, "r")
        w2 = os.fdopen(w2, "w")
        child_to_parent_pipes[i]["in"] = r1
        child_to_parent_pipes[i]["out"] = w2
        parent_to_child_pipes[i]["in"] = r2
        parent_to_child_pipes[i]["out"] = w1
    return child_to_parent_pipes, parent_to_child_pipes


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

    output = sys.stdout
    debug = False
    inputs = []
    fragment_size = 0
    proc = 1

    # check given options
    for i in range(len(opts)):
        opt, arg = opts[i]
        if opt == "-i" or opt == "--input":
            inputs.extend(arg.split(","))
        elif opt == "-h" or opt == "--help":
            print_help()
            exit()
        elif opt == "-d" or opt == "--debug":
            debug = True
        elif opt == "-c" or opt == "--config":
            config(str(arg))
        elif opt == "-f" or opt == "--file":
            inputs.extend(get_input_from_file(arg))
        elif opt == "-o" or opt == "--output":
            output = open(arg, "w")
        elif opt == "-p" or opt == "--proc":
            proc = 4
        elif opt == "-s" or opt == "--size":
            if arg.isdigit():
                fragment_size = int(arg)

    if len(inputs) == 0:
            print("No input given!")
            print("Try '-h' for help.")
            exit()

    # init pipes
    child_to_parent_pipes, parent_to_child_pipes = get_pipes(proc)

    # children
    for i in range(proc):
        pid = os.fork()
        if pid == 0:
            # close unused pipes
            for j in range(proc):
                parent_to_child_pipes[j]["out"].close()
                parent_to_child_pipes[j]["in"].close()
                if i != j:
                    child_to_parent_pipes[j]["in"].close()
                    child_to_parent_pipes[j]["out"].close()

            calculate_sqrt_child_proc(child_to_parent_pipes[i]["in"],
                                      child_to_parent_pipes[i]["out"], debug)
            os._exit(0)

    # parent
    for i in range(proc):
        child_to_parent_pipes[i]["in"].close()
        child_to_parent_pipes[i]["out"].close()

    input_size = len(inputs)

    # check fragment size
    if fragment_size <= 0 or fragment_size > input_size:
        fragment_size = math.ceil(input_size / proc)

    steps = []
    for i in range(0, input_size, fragment_size):
        steps.append(i)
    steps.append(input_size)

    # write data to children
    for j in range(len(steps)-1):
        i = j % proc
        data = ",".join(inputs[steps[j]:steps[j+1]])
        data += "\n"
        parent_to_child_pipes[i]["out"].write(data)
        parent_to_child_pipes[i]["out"].flush()

    # close ouput pipes
    for i in range(proc):
        parent_to_child_pipes[i]["out"].close()

    # get results from children in proper order
    results = ""
    for j in range(len(inputs)):
        k = int(j / fragment_size)
        i = k % proc
        results += parent_to_child_pipes[i]["in"].readline()

    for i in range(proc):
        parent_to_child_pipes[i]["in"].close()

    print(results, file=output)


# default sqrt2 values
start = 1
loops = 100
tolerance = 1e-14

# precision, used for Decimal
prec = 25

shortopts = "hdi:c:f:o:ps:"
longopts = ["help", "debug", "input=", "config=", "file=", "output=",
            "proc", "size="]

if __name__ == "__main__":
    main()
