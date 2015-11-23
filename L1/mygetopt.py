#!/usr/bin/env python3

import sys
import subprocess
from getopt import getopt
from getopt import GetoptError
import helper
import menu
import logging


def version():
    logging.info("Printing git token")
    print("Git Token: ", flush=True)
    subprocess.call("git rev-parse --short HEAD", shell=True,
                    stdout=sys.stdout)
    print()


def myhelp():
    logging.info("Printing help")
    print("HELP")
    print("\t{} [OPTIONS]".format(sys.argv[0]))
    print("Possible options:")
    print("\t-v , --version")
    print("\t\tGIT Token")
    print("\t-h , --help")
    print("\t\tshow Help")
    print("\t-o , --output [FILE]")
    print("\t\twrite output into FILE")
    print("\t-p , --python")
    print("\t\tshow python version")
    print("\t-s , --system")
    print("\t\tshow system informations")
    print("\t-c , --cpu")
    print("\t\tshow cpu informations")
    print("\t-m , --memory [all/size/resident/share/text]")
    print("\t\tshow memory usage")
    print()


def python():
    logging.info("Printing python info")
    menu.option_one()
    print()


def system():
    logging.info("Printing system info")
    menu.option_two()
    print()


def cpu():
    logging.info("Printing cpu info")
    menu.option_three()


def memory(s):
    logging.info("Printing memory info")
    if s == "all":
        dic = helper.memory_sum()
        print("Memory:")
        print("size\t\t{:.2f} MB".format(dic["size"]))
        print("resident\t{:.2f} MB".format(dic["resident"]))
        print("share\t\t{:.2f} MB".format(dic["share"]))
        print("text\t\t{:.2f} MB".format(dic["text"]))
        print("SUM\t\t{:.2f} MB".format(dic["SUM"]))
    else:
        ls = helper.memory_top(s)
        if ls is None:
            myhelp()
            return

        for i in range(10):
            print("{:d}. {}:\t{:.2f} MB".format(i + 1, ls[i][0], ls[i][1]))
    print()


def main():

    logging.basicConfig(filename="mygetopt.log", level=logging.INFO)
    logging.info("Started")

    try:
        opts, args = getopt(sys.argv[1:], shortopts, longopts)
    except GetoptError:
        print("Wrong Arguments!")
        print()
        myhelp()
        logging.info("Finished: Programm call with wrong arguments")
        exit()

    for i in range(len(opts)):
        opt, arg = opts[i]
        if opt == "-o" or opt == "--output":
            sys.stdout = open(arg, "w")

    for i in range(len(opts)):
        opt, arg = opts[i]
        if opt == "-v" or opt == "--version":
            version()
        elif opt == "-h" or opt == "--help":
            myhelp()
        elif opt == "-p" or opt == "--python":
            python()
        elif opt == "-s" or opt == "--system":
            system()
        elif opt == "-c" or opt == "--cpu":
            cpu()
        elif opt == "-m" or opt == "--memory":
            memory(arg)

    logging.info("Finished normal")


shortopts = "vho:pscm:"
longopts = ["version", "help", "output=", "python", "system", "cpu",
            "memory="]

if __name__ == "__main__":
    main()
