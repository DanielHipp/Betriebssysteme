#!/usr/bin/env python3

import sys
import random


def makeMatrix(rows, columns, minimum, maximum):
	matrix = [[random.uniform(minimum, maximum) for j in range(columns)] \
                for i in range(rows)]
	return matrix


def main():
    if len(sys.argv) != 5:
        print("Only four numbers and the programmname are needed!: "
                "rows, columns, minimum and maximum!")
        exit()

    try:
        rows = int(sys.argv[1])
        columns = int(sys.argv[2])
        minimum = int(sys.argv[3])
        maximum = int(sys.argv[4])
    except:
        print("Illegal Argument!")
        exit()

    m = makeMatrix(rows, columns, minimum, maximum)
    for i in range(rows):
        row = []
        for j in range(columns):
            row.append("{:.5f}".format(m[i][j]))
        print(" ".join(row))


if __name__ == "__main__":
    main()
