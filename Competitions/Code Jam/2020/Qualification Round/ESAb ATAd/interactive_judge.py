import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue

VERBOSE = False

global process, verdict, input_queue
global b, array
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict, array, b

    line = input_queue.get().decode().strip()
    if VERBOSE: print("program:", line, flush=True)

    if line[0] == '!':
        return read_process()

    if len(line) == b:
        if VERBOSE: print("correct:", ''.join(array))
        if list(line) != array:
            verdict = "Wrong Answer"
            print(line, ' ', ''.join(array))
            feed_process("N")
        else:
            feed_process("Y")
        return False
    else:
        p = int(line)
        if p < 0 or p > b:
            feed_process("N")
        else:
            feed_process(array[p - 1])
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
b = 100
feed_process("%d %d" % (testCases, b))
for t in range(testCases):
    array = ""
    for i in range(b):
        array += chr(ord('0') + randint(0, 1))
    array = list(array)
    q = 0
    while True:
        if q % 10 == 0:
            op = randint(0, 3)
            if op == 0: # flip
                for i in range(b):
                    array[i] = '1' if array[i] == '0' else '0'
            if op == 1: # reverse
                for i in range(b // 2):
                    array[i], array[b - i - 1] = array[b - i - 1], array[i]
            if op == 2: # both
                for i in range(b):
                    array[i] = '1' if array[i] == '0' else '0'
                for i in range(b // 2):
                    array[i], array[b - i - 1] = array[b - i - 1], array[i]
            if op == 3: # nothing
                pass
            if VERBOSE: print("QUANTUM FLUCTUATION (%d):" % op, ''.join(array))
        q += 1
        if not read_process():
            break

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())