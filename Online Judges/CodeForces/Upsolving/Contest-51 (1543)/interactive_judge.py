from hashlib import new
import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue

VERBOSE = True

global process, n, k, verdict, input_queue
global password
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict, password

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    guess = int(line)

    if guess == password:
        feed_process(str(1))
        return False
    else:
        print("\t\t%d xor_%d %d -> %d" % (guess, k, password, guess ^ password))
        new_password, p = 0, 1
        while password > 0 or guess > 0:
            a, b = password % k, guess % k
            new_password += p * (((a - b) % k + k) % k)
            p *= k
            password //= k
            guess //= k
        password = new_password
        feed_process(str(0))
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

testCases = 10
feed_process(str(testCases))
for t in range(testCases):
    n, k = randint(1, 10), randint(2, 10)
    password = randint(0, n - 1)

    # if t == 0:
    #     n, k = 5, 2
    #     password = 3
    # else:
    #     n, k = 5, 3
    #     password = 2

    feed_process("%d %d" % (n, k))
    cnt = 1
    while read_process() and cnt <= n:
        cnt += 1
        pass
    if cnt == n + 1:
        verdict = "Wrong Answer"
        break

process.stdin.close()
# if queries > (n >> 1):
#     verdict = "Wrong Answer"
print("Verdict:", verdict, "| n:", n, "| limit:", (n >> 1), "| queries:", 0)
exit(process.wait())