import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random, shuffle
from queue import Queue

VERBOSE = True

global process, curr_number, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    guess = int(line[1:])
    if line[0] == '!':
        if guess != curr_number:
            verdict = "Wrong Answer"
        return False
    elif line[0] == '?':
        if guess < curr_number: feed_process(">")
        elif guess == curr_number: feed_process("=")
        else: feed_process("<")
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

maxN = 10
testCases = randint(1, 1)
feed_process("%d" % testCases)
for t in range(testCases):
    n = randint(1, maxN)
    k = randint(1, n)
    missing = [i for i in range(1, n + 1)]
    shuffle(missing)
    feed_process("%d %d" % (l, r))
    while read_process():
        pass

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())