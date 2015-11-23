import sys
import platform
import os
import resource
import logging


def python_info():
    logging.info("Getting python info")
    return platform.python_version()


def system_info():
    logging.info("Getting system info")

    info = {}

    info["system"] = platform.system()
    info["release"] = platform.release()
    info["version"] = platform.version()
    info["node"] = platform.node()
    info["architecture"] = platform.architecture()[0]
    info["name"] = platform.uname()
    info["distribution"] = platform.linux_distribution()[0]
    info["distribution_release"] = platform.linux_distribution()[1]
    info["processor"] = platform.processor()
    info["machine"] = platform.machine()

    return info


def codename(model, family):
    logging.info("Searching codename")

    model = "0x{0:02X}".format(int(model))
    family = "0x{0:02X}".format(int(family))

    with open("proc_code.txt") as f:
        for line in f:
            words = line.rstrip("\n").split(":")
            for i in range(len(words)):
                words[i] = words[i].strip()
            if (words[2] == family and words[3] == model):
                logging.info("Codename found")
                return words[0]

    logging.warning("Codename not found")
    return "Not Found"


def cpu_info():
    logging.info("Getting cpu info")
    n = -1
    info = {}

    with open('/proc/cpuinfo') as f:
        for line in f:
            if line.startswith('cpu family'):
                n = n + 1
                info[n] = {}
                info[n]["fam"] = line.rstrip('\n').split(':')[1]
            elif line.startswith('model name'):
                info[n]["name"] = line.rstrip('\n').split(':')[1]
            elif line.startswith('model'):
                info[n]["model"] = line.rstrip('\n').split(':')[1]
            elif line.startswith('cpu MHz'):
                info[n]["mhz"] = line.rstrip('\n').split(':')[1]
            elif line.startswith('flags') or line.startswith("Features"):
                if 'lm' in line.rstrip('\n').split():
                    info[n]["arch"] = "64 Bit"
                else:
                    info[n]["arch"] = "32 Bit"

    for i in range(n + 1):
        info[i]["codename"] = codename(info[i]["model"], info[i]["fam"])

    return info, n + 1


def memory_sum():
    logging.info("Getting memory all")
    dic = {}
    dic["size"] = 0
    dic["resident"] = 0
    dic["share"] = 0
    dic["text"] = 0
    dic["SUM"] = 0
    pids = []
    for pid in os.listdir("/proc"):
        if pid.isdigit():
            pids.append(pid)
    for pid in pids:
        try:
            with open("/proc/{}/statm".format(pid)) as f:
                mem = f.read().split()

                dic["size"] += int(mem[0])
                dic["resident"] += int(mem[1])
                dic["share"] += int(mem[2])
                dic["text"] += int(mem[3])
                dic["SUM"] += int(mem[0]) + int(mem[1]) + int(mem[2]) + \
                    int(mem[3])  # + int(mem[5])
        except FileNotFoundError:
            logging.error("/proc/{}/statm not found".format(pid))
            continue

    pagesize = resource.getpagesize()

    for key in dic:
        dic[key] *= pagesize / 2**20

    return dic


def memory_top(opt):
    logging.info("Getting memory {}".format(opt))

    pids = []
    ls = []
    split = 0

    if opt == "size":
        split = 0
    elif opt == "resident":
        split = 1
    elif opt == "share":
        split = 2
    elif opt == "text":
        split = 3
    else:
        return

    pagesize = resource.getpagesize()

    for pid in os.listdir("/proc"):
        if pid.isdigit():
            pids.append(pid)
    for pid in pids:
        try:
            with open("/proc/{}/statm".format(pid)) as statm:
                with open("/proc/{}/cmdline".format(pid)) as cmdline:
                    name = cmdline.read().split("/")
                    name = name[len(name) - 1].rstrip("\x00")
                    mem = statm.read().split()
                    mem = int(mem[split]) * pagesize / 2**20
                    ls.append((name, mem))
        except FileNotFoundError:
            logging.error("/proc/{}/statm not found".format(pid))
            continue
    ls.sort(key=lambda ls: ls[1], reverse=True)
    return ls
