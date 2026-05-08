import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random, shuffle
from queue import Queue

VERBOSE = False

global process, impostor_pos, players, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

RESPONSE_MAP = [[1, 0, 1], [0, 1, 0], [0, 1]]

def read_process():
    global verdict

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    if line[0] == '!':
        guess = int(line[1:]) - 1
        if guess != impostor_pos:
            verdict = "Wrong Answer"
            feed_process("-1")
        return False
    elif line[0] == '?':
        a, b = list(map(int, line[1:].split()))
        a, b = a - 1, b - 1
        feed_process(str(RESPONSE_MAP[players[a]][players[b]]))
    elif line[0] == '#':
        if not VERBOSE: print("program:", line, flush=True)
    return True

def process_input_handler(data):
    for line in data:
        input_queue.put(line)
    data.close()

def feed_process(string):
    if VERBOSE: print("judge  :", string)
    process.stdin.write((string.strip() + "\n").encode())

if os.system("g++ %s -o test -std=c++23 -O2" % code_path) != 0:
    exit(0)
print("Compiled %s successfully!" % code_path)

process = Popen(['./test'], stdin=PIPE, stdout=PIPE, bufsize=0)
Thread(target=process_input_handler, args=(process.stdout,)).start()

testCases = int(1e2)
feed_process("%d" % testCases)
for t in range(testCases):
    # print("------------")
    n = randint(3, int(100))

    players = [randint(0, 1) for _ in range(n)]
    impostor_pos = randint(0, n - 1)
    # players = [0, 0, 2, 0, 0]
    # impostor_pos = 2
    players[impostor_pos] = 2

    feed_process("%d" % n)
    while read_process():
        pass

    if verdict != "Accepted":
        print("WA!! on: ")
        print("\t", players, " | ", impostor_pos, sep="")
        break

process.stdin.close()
print("Verdict:", verdict)
exit(process.wait())