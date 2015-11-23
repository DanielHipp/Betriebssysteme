#!/usr/bin/env python3 -tt

import helper
from colorama import init, Fore, Style


def print_line():
    print("------------------------------")


def print_menu():
    print("{0}: Python Info".format(1))
    print("{0}: System Info".format(2))
    print("{0}: CPU Info".format(3))
    print("{0}: Quit menu.py".format("q"))


def print_options():
    print("Choose ['{0}', '{1}', '{2}', '{3}']: ".format(1, 2, 3, "q"),
          end="")


def option_one():
    print("Python Version: {0}".format(helper.python_info()))


def option_two():
    info = helper.system_info()
    indent = "25"

    print("{1:{0:s}s}{2:s}".format(indent, "LABEL", "CONTENT"))

    print("{1:{0:s}s}{2:s}".format(indent, "System", info["system"]))
    print("{1:{0:s}s}{2:s}".format(indent, "Architecture",
          info["architecture"]))
    print("{1:{0:s}s}{2:s}".format(indent, "Node", info["node"]))

    if info["system"] == "Linux":
        print("{1:{0:s}s}{2:s}".format(indent, "Distribution",
              info["distribution"]))
        print("{1:{0:s}s}{2:s}".format(indent, "Distribution Release",
              info["distribution_release"]))
    else:
        print("{1:{0:s}s}{2:s}".format(indent, "Processor", info["processor"]))
        print("{1:{0:s}s}{2:s}".format(indent, "Version", info["version"]))


def option_three():
    info, n = helper.cpu_info()

    print("Number of CPUs: " + str(n))
    print()

    for i in range(n):
        print("Processor #{0}:".format(i))
        print("Modelname:\t{0}".format(info[i]["name"]))
        print("Architecture:\t {0}".format(info[i]["arch"]))
        print("Model:\t\t{0}".format(info[i]["model"]))
        print("Family:\t\t{0}".format(info[i]["fam"]))
        print("Frequency:\t{0} MHz".format(info[i]["mhz"]))
        print("Codename:\t {0}".format(info[i]["codename"]))
        print()


def option_quit():
    exit(0)


def main():
    init()
    print_menu()
    print_line()

    while (1):
        try:
            print(Style.BRIGHT, end="")
            print_options()
            print(Style.RESET_ALL, end="")
            choice = input()
            print_line()
            options[choice]()
            print_line()
        except KeyError:
            print(Fore.RED + "Illegal Argument!")
            print(Style.RESET_ALL, end="")
            print_line()

options = {"1": option_one, "2": option_two, "3": option_three,
           "q": option_quit}

if __name__ == "__main__":
    main()
