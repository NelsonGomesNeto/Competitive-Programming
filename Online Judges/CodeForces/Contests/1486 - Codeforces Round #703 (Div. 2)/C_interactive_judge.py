import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random, shuffle
from queue import Queue

VERBOSE = True

global process, a, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    if line[0] == '!':
        pos = int(line[1:])
        if max(a) != a[pos - 1]:
            verdict = "Wrong Answer"
        return False
    elif line[0] == '?':
        lo, hi = map(int, line[1:].split())
        biggest = max(a[lo - 1 : hi])
        # print(">>", lo, hi, a[lo - 1 : hi], list(range(lo - 1, hi)), biggest)
        curr = -1
        for i in range(lo - 1, hi):
            if (curr == -1 or a[i] > a[curr]) and a[i] != biggest:
                curr = i
        feed_process("%d" % (curr + 1))
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

testCases = randint(1, 10)
for t in range(testCases):
    n = randint(2, int(1e5))
    feed_process("%d" % n)
    a = [i + 1 for i in range(n)]
    shuffle(a)
    print(">>>> started with:", n)
    while read_process():
        pass

    if verdict == "Wrong Answer":
        biggest = max(a)
        for i in range(n):
            if a[i] == biggest:
                print(">> biggest:", i + 1, biggest)
        break

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())