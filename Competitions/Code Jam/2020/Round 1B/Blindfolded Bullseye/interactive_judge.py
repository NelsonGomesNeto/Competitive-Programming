import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue
from math import sqrt

EPS = 1e-7
VERBOSE = True

global process, curr_number, verdict, input_queue
global r, x, y
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def dist(x1, y1, x2, y2):
    return sqrt((x1 - x2)**2 + (y1 - y2)**2)

def read_process():
    global verdict

    line = input_queue.get().decode().strip()
    if VERBOSE: print("program:", line, flush=True)

    if (line[0] == '!'): return True

    gx, gy = map(int, line.split())
    if x == gx and y == gy:
        feed_process("CENTER")
        return False
    elif dist(x, y, gx, gy) <= r + EPS:
        feed_process("HIT")
    else:
        feed_process("MISS")
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

maxX = int(1e9)

testCases = randint(1, 10)
a = randint(maxX // 2, maxX // 2)
b = randint(a, maxX // 2)
feed_process("%d %d %d" % (testCases, a, b))
for t in range(testCases):
    r = randint(a, b)
    x, y = randint(-maxX + r, maxX - r), randint(-maxX + r, maxX - r)
    print('current circle:', x, y, r)
    c = 0
    while read_process() and c <= 300:
        c += 1
        pass
    if c > 300:
        verdict = "Wrong Answer"

print("Verdict:", verdict)
process.stdin.close()
exit(process.wait())