import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue

VERBOSE = True

global process, n, arr, k, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict, arr, n, k

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)

    kind, nums = line.split(' ')[0], list(map(int, line.split(' ')[1:]))

    if kind == 'finish':
        if nums[0] != sorted(arr)[k - 1]:
            verdict = "Wrong Answer"
        return False
    elif kind in ("and", "or"):
        if kind == 'and':
            feed_process("%d" % (arr[nums[0] - 1] & arr[nums[1] - 1]))
        else:
            feed_process("%d" % (arr[nums[0] - 1] | arr[nums[1] - 1]))
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
    # n = randint(3, int(3))
    # k = randint(1, n)
    # arr = [randint(0, int(5)) for _ in range(n)]
    n = 3
    k = 3
    arr = [3, 5, 1]
    print(n, k, arr)
    feed_process("%d %d" % (n, k))
    while read_process():
        pass
    if verdict == "Wrong Answer":
        break

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())