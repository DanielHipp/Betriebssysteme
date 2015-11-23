#!/usr/bin/env python3

from getopt import getopt
from getopt import GetoptError
import sys
import os
import collections
from prettytable import PrettyTable


def get_env():
    env = {}
    env["CWD"] = os.getcwd()
    env["Home"] = os.getenv("HOME")
    env["PWD"] = os.getenv("PWD")
    env["Path"] = os.getenv("PATH")
    env["Shell"] = os.getenv("SHELL")
    env["User"] = os.getenv("USER")
    env["UID"] = os.getuid()
    env["GID"] = os.getgid()
    env["VEnv"] = os.getenv("VIRTUAL_ENV")
    return env


def get_ppids(pid):
    pidlist = []

    pidlist.append(pid)
    while pid != 1:
        f = os.popen("ps -o ppid= {}".format(pid))
        pid = int(f.readline())
        pidlist.append(pid)
        f.close()

    return pidlist


def get_state(pid):
    state = ""
    with open("/proc/{}/stat".format(pid)) as f:
        line = f.readline()
        state = line.split(" ")[2]
    return state


def get_name(pid):
    name = ""

    with open("/proc/{}/status".format(pid)) as f:
        line = f.readline()
        name = line.split(":")[1].strip()

    return name


def get_tree():
    pidtree = collections.OrderedDict()
    pidlist = get_ppids(os.getpid())

    for i in range(len(pidlist)):
        pid = pidlist[i]
        pidtree[i] = (pid, get_name(pid), get_state(pid))

    return pidtree


def print_env():
    env = get_env()
    print("CWD:\t{}".format(env["CWD"]))
    print("Home:\t{}".format(env["Home"]))
    print("PWD:\t{}".format(env["PWD"]))
    print("Path:\t{}".format(env["Path"]))
    print("Shell:\t{}".format(env["Shell"]))
    print("User:\t{}".format(env["User"]))
    print("UID:\t{}".format(env["UID"]))
    print("GID:\t{}".format(env["GID"]))
    print("VEnv:\t{}".format(env["VEnv"]))


def print_pidtree():
    pidtree = get_tree()
    table = PrettyTable(["PID", "Name", "Status"])

    for key in pidtree:
        pid, name, state = pidtree[key]
        table.add_row([pid, name, state])

    print(table)


def print_help():
    print("Possible options:")
    print("\t-e, --env")
    print("\t-p, --pidtree")


def main():
    try:
        opts, args = getopt(sys.argv[1:], shortopts, longopts)
    except GetoptError:
        print("Illegal Arguments!")
        print_help()
        exit()

    if len(opts) == 0:
        print_help()
        exit()

    for i in range(len(opts)):
        opt, arg = opts[i]

        if opt == "-e" or opt == "--env":
            print_env()
        if opt == "-p" or opt == "--pidtree":
            print_pidtree()


shortopts = "ep"
longopts = ["env", "pidtree"]

if __name__ == "__main__":
    main()
