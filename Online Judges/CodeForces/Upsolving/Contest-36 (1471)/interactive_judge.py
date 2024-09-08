import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue

VERBOSE = True

global process, p, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    pos = int(line[1:]) - 1
    if line[0] == '!':
        if pos != p:
            verdict = "Wrong Answer"
        return False
    elif line[0] == '?':
        feed_process(str(a[pos]))
        n = len(a)
        aux = [0]*n
        for i in range(n):
            prv, nxt = ((i - 1) % n + n) % n, (i + 1) % n
            if i == p:
                aux[nxt] += a[i]
            else:
                aux[prv] += a[i] // 2
                aux[nxt] += a[i] // 2 + (a[i] % 2 != 0)
        for i in range(n):
            a[i] = aux[i]
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

testCases = randint(1, 1000)
# feed_process("%d" % testCases)
for t in range(testCases):
    n = randint(int(4), int(5))
    p = randint(0, n - 1)
    k = 2# 2*randint(1, int(1e9) // 2)
    a = [k]*n
    feed_process("%d %d" % (n, k))
    print("\tstarted", n, p, k)
    while read_process():
        pass
    if verdict == "Wrong Answer":
        print(a)
        break

process.stdin.close()
print("Verdict:", verdict, p + 1, k)
exit(process.wait())