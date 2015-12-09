#!/usr/bin/env python3

import sys
from getopt import getopt
from getopt import GetoptError
import random


def main():
    if len(sys.argv) != 2 or not sys.argv[1].isdigit():
        print("Illegal argument!")
        print("call: {} [number]".format(sys.argv[0]))
        exit()

    for i in range(int(sys.argv[1])):
        print(str(random.uniform(0, 1000000)))


if __name__ == "__main__":
    main()
