import sys
import os
import time
from subprocess import PIPE, Popen
from threading import Thread
from random import randint, random
from queue import Queue

VERBOSE = True

global process, n, verdict, input_queue
verdict = "Accepted"
input_queue = Queue()

args = sys.argv
code_path = args[1]

def read_process():
    global verdict, queries

    line = input_queue.get().decode().strip()

    if VERBOSE: print("program:", line, flush=True)
    if line[0] == '!':
        invalid = False
        for _ in range(n - 1):
            line = input_queue.get().decode().strip()
            u, v = map(int, line.split(" "))
            print("program:", u, v, flush=True)
            if not v in tree[u] or not u in tree[v]:
                invalid = True
        if invalid == True:
            verdict = "Wrong Answer"
        return False
    elif line[0] == '?':
        queries += 1
        node = int(line[1:])
        d = get_distances(node)
        feed_process(" ".join([str(dd) for dd in d]))
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

global parents
parents = []
def root(u):
    global parents
    if parents[u] < 0:
        return u
    parents[u] = root(parents[u])
    return parents[u]
def merge(u, v):
    u, v = root(u), root(v)
    if u == v: return
    if parents[u] > parents[v]:
        u, v = v, u
    parents[u] += parents[v]
    parents[v] = u

global tree
tree = []
def build_tree(n: int):
    global parents, tree
    tree = [[] for i in range(n + 1)]
    parents = [-1]*(n + 1)
    for _ in range(n - 1):
        u, v = 1, 1
        while root(u) == root(v):
            u, v = randint(1, n), randint(1, n)
        merge(u, v)
        tree[u] += [v]
        tree[v] += [u]
def print_tree(u: int = 1, prv: int = -1, depth: int = 0):
    print("\t"*depth, u)
    for v in tree[u]:
        if v != prv:
            print_tree(v, u, depth + 1)
def dfs(d, u: int = 0, prv: int = -1, depth: int = 0):
    d[u] = depth
    for v in tree[u]:
        if v != prv:
            dfs(d, v, u, depth + 1)
def get_distances(source: int):
    d = [0]*(n + 1)
    dfs(d, source)
    return d[1:]

testCases = 1
global queries
queries = 0
for t in range(testCases):
    n = randint(10, 20)
    build_tree(n)
    print_tree()
    feed_process("%d" % n)
    while read_process():
        pass

process.stdin.close()
if queries > (n >> 1):
    verdict = "Wrong Answer"
print("Verdict:", verdict, "| n:", n, "| limit:", (n >> 1), "| queries:", queries)
exit(process.wait())