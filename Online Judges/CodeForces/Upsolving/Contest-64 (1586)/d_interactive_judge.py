import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random, shuffle
from queue import Queue

VERBOSE = True

global process, n, p, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict
    global n, p

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    if line[0] == '?':
        a = list(map(int, line[2:].split(" ")))
        assert(len(a) == n)
        s = [a[i] + p[i] for i in range(n)]
        k = 0
        has = {}
        for i in range(n):
            if s[i] in has:
                k = has[s[i]]
                break
            has[s[i]] = i + 1
        feed_process(str(k))
    elif line[0] == '#':
        return True
    else:
        a = list(map(int, line[2:].split(" ")))
        if (a != p):
            verdict = "Wrong Answer"
        return False

    return True

def process_input_handler(data):
    for line in data:
        input_queue.put(line)
    data.close()

def feed_process(string):
    if VERBOSE: print("judge  :", string)
    process.stdin.write((string.strip() + "\n").encode())

if os.system("g++ %s -o test -std=c++17" % code_path) != 0:
    exit(0)
print("Compiled %s successfully!" % code_path)

process = Popen(['./test'], stdin=PIPE, stdout=PIPE, bufsize=0)
Thread(target=process_input_handler, args=(process.stdout,)).start()

testCases = randint(1, 100)
for t in range(testCases):
    n = randint(2, 20)
    p = list(range(1, n + 1))
    shuffle(p)
    print("hidden: ", n, p)
    feed_process("%d" % (n))
    while read_process():
        pass

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())