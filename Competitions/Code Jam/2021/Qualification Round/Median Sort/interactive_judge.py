import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random, shuffle
from queue import Queue


global process, n, verdict, input_queue, total_queries
total_queries = 0
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]
VERBOSE = True if len(args) == 2 else eval(args[2])

def read_process():
    global verdict, n, total_queries

    line = input_queue.get().decode().strip()

    if line[0] == '#':
        print("program:", line, flush=True)
        return True
    if VERBOSE: print("program:", line, flush=True)

    guess = list(map(int, line.split()))
    if len(guess) == n:
        can1, can2 = True, True
        for i in range(n):
            if guess[i] != x[i]:
                can1 = False
        guess = list(reversed(guess))
        for i in range(n):
            if guess[i] != x[i]:
                can2 = False
        if not can1 and not can2:
            verdict = "Wrong Answer"
        return False
    else:
        total_queries += 1

        values = [pos[i] for i in guess]
        if len(set(values)) < 3:
            feed_process(str(list(set(values))[0]))
        else:
            minimum, maximum = min(values), max(values)
            for i in range(3):
                if pos[guess[i]] != minimum and pos[guess[i]] != maximum:
                    feed_process(str(guess[i]))
    return True

def process_input_handler(data):
    for line in data:
        input_queue.put(line)
    data.close()

def feed_process(string: str):
    if VERBOSE: print("judge  :", string)
    process.stdin.write((string.strip() + "\n").encode())

if os.system("g++ %s -o test -std=c++17" % code_path) != 0:
    exit(0)
print("Compiled %s successfully!" % code_path)

process = Popen(['./test'], stdin=PIPE, stdout=PIPE, bufsize=0)
Thread(target=process_input_handler, args=(process.stdout,)).start()

testCases = 100
n = 50
q = 300 * testCases
feed_process("%d %d %d" % (testCases, n, q))
for t in range(testCases):
    x = list(range(1, n + 1))
    shuffle(x)
    # x = [2, 4, 1, 3]
    # x = [5, 4, 3, 2, 1]
    # x = [1, 4, 3, 2, 5]
    # x = [1, 3, 5, 4, 2]
    # x = [5, 2, 3, 1, 4]
    # x = [2, 4, 3, 5, 1]
    # x = [2, 5, 3, 4, 1]
    # x = [6, 9, 4, 2, 5, 8, 10, 1, 3, 7]
    # x = [6, 7, 1, 5, 4, 2, 10, 3, 8, 9]
    # x = [3, 1, 10, 8, 6, 7, 9, 2, 4, 5]
    # x = [5, 6, 3, 1, 8, 9, 4, 2, 10, 7]
    pos = [0]*(n + 1)
    for i in range(n):
        pos[x[i]] = i
    if VERBOSE:
        print(">>> new test case: ", n, x)
    while read_process():
        pass
    feed_process("1")

process.stdin.close()
print("Verdict:", verdict)
print("TotalQueries:", total_queries)
exit(process.wait())