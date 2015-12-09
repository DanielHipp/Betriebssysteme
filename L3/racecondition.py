#!/usr/bin/env python3

import sys
import os
from threading import Thread
import threading
import time
from getopt import getopt
from getopt import GetoptError


def print_help():
    print("HELP")
    print("\t{} [OPTIONS]".format(sys.argv[0]))
    print("Possible options:")
    print("\t-h , --help")
    print("\t\tshow help")
    print("\t-t , --threads [NUMBER]")
    print("\t\tstart NUMBER threads")
    print("\t-l , --loops [NUMBER]")
    print("\t\tdo NUMBER loops")
    print("\t-g , --gil")
    print("\t\tuse standard global interpreter lock")
    print("\t-m , --mutex")
    print("\t\tuse a mutex")
    print("\t-p , --peterson]")
    print("\t\tuse the peterson algorithm")


def race_lock(n_threads, n_loops):
    threads = []
    for i in range(n_threads):
        t = Thread(target=increment_race_lock, args=(n_loops, ))
        t.start()
        threads.append(t)

    for t in threads:
        t.join()

    return n_threads * n_loops, global_var


def increment_race_lock(loops):
    global global_var
    for i in range(loops):
        global_var += 1


def race(n_threads, n_loops):
    threads = []
    for i in range(n_threads):
        t = Thread(target=increment_race, args=(n_loops, ))
        t.start()
        threads.append(t)

    for t in threads:
        t.join()

    return n_threads * n_loops, global_var


def increment_race(loops):
    global global_var
    for i in range(loops):
        local_var = global_var
        time.sleep(0.001)
        global_var = local_var + 1


def race_m(n_threads, n_loops):
    threads = []
    lock = threading.Lock()
    for i in range(n_threads):
        t = Thread(target=increment_mutex, args=(n_loops, lock))
        t.start()
        threads.append(t)

    for t in threads:
        t.join()

    return n_threads * n_loops, global_var


def increment_mutex(loops, lock):
    global global_var
    for i in range(loops):
        lock.acquire()
        local_var = global_var
        time.sleep(0.001)
        global_var = local_var + 1
        lock.release()


def race_p(n_threads, n_loops):
    threads = []
    global level
    global last_to_enter

    for i in range(n_threads):
        t = Thread(target=increment_peterson, args=(n_loops, i))
        threads.append(t)
        level.append(-1)

    for i in range(n_threads - 1):
        last_to_enter.append(-1)

    for t in threads:
        t.start()

    for t in threads:
        t.join()

    return n_threads * n_loops, global_var


def increment_peterson(loops, proc_number):
    global global_var
    global level
    global last_to_enter

    for i in range(loops):
        for l in range(len(level)-1):
            level[proc_number] = l
            last_to_enter[l] = proc_number
            while last_to_enter[l] == proc_number and \
                    exists_higher_level_proc(proc_number):
                continuel

        local_var = global_var
        time.sleep(0.001)
        global_var = local_var + 1

        level[proc_number] = -1


def exists_higher_level_proc(proc_number):
    proc_level = level[proc_number]
    for i in range(len(level)):
        if i == proc_number:
            continue
        if level[i] >= proc_level:
            return True
    return False


def print_text(exp, cur):
    print("After {:d} modifications, "
          "global_var should have become {:d}".format(exp, exp))
    print("After {:d} modifications, global_var is {:d}".format(exp, cur))


def main():
    try:
        opts, args = getopt(sys.argv[1:], shortopts, longopts)
    except GetoptError:
        print("Illegal Arguments!")
        print("Try '-h' for help.")
        exit()

    threads = 40
    loops = 10
    mutex = False
    peterson = False
    gil = False

    for i in range(len(opts)):
        opt, arg = opts[i]
        if opt == "-t" or opt == "--threads":
            if not arg.isdecimal():
                print("'{}' isn't a correct number!".format(arg))
                exit()
            threads = int(arg)
        elif opt == "-h" or opt == "--help":
            print_help()
            exit()
        elif opt == "-l" or opt == "--loops":
            if not arg.isdecimal():
                print("'{}' isn't a correct number!".format(arg))
                exit()
            loops = int(arg)
        elif opt == "-m" or opt == "--mutex":
            mutex = True
        elif opt == "-p" or opt == "--peterson":
            peterson = True
        elif opt == "-g" or opt == "--gil":
            gil = True

    global global_var

    if not(peterson or mutex or gil):
        print("Race Condition:")
        exp, cur = race(threads, loops)
        print_text(exp, cur)
        exit()
    if peterson:
        global_var = 0
        print("Peterson:")
        exp, cur = race_p(threads, loops)
        print_text(exp, cur)
    if mutex:
        global_var = 0
        print("Mutex:")
        exp, cur = race_m(threads, loops)
        print_text(exp, cur)
    if gil:
        global_var = 0
        print("Gil:")
        exp, cur = race_lock(threads, loops)
        print_text(exp, cur)


global_var = 0

level = []
last_to_enter = []

shortopts = "t:l:hmpg"
longopts = ["help", "threads=", "loops=", "mutex", "peterson", "gil"]

if __name__ == "__main__":
    main()
