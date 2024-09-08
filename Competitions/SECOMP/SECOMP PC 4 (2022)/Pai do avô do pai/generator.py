import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

shutil.rmtree("tests", ignore_errors=True)
os.mkdir("tests")

tree = []
def dfs(u = 0, prv = -1, depth = 0):
    print("  " * depth, u)
    for v in tree[u]:
        dfs(v, u, depth + 1)

test_cases = int(input())
for t in range(1, test_cases + 1):
    # break
    n = 6
    parents = [-1, 0, 1, 1, 0, 2, 3]
    tree = [[] for i in range(n)]
    for i in range(1, n):
        tree[parents[i]].append(i)
    print("Tree:")
    dfs()
    # f = open("tests/%d.in" % t, "w")

    # n = randint(2, int(10))
    # print(n, file=f)

    # parents = [-1 if i == 0 else randint(0, i - 1) for i in range(n)]
    # print(*parents[1:], file=f)

    # tree = [[] for i in range(n)]
    # for i in range(1, n):
    #     tree[parents[i]].append(i)
    # # print("Tree:")
    # # dfs()

    # height = [0] * n
    # height[0] = 1
    # for i in range(1, n):
    #     height[i] = height[parents[i]] + 1

    # q = randint(1, int(10))
    # print(q, file=f)
    # for _ in range(q):
    #     u = randint(0, n - 1)
    #     k = randint(1, height[u])
    #     print(u, k, file=f)

    # f.close()

for filename in os.listdir("tests"):
    if ".in" in filename:
        out_filename = filename.replace(".in", ".out")
        os.system("./test < tests/%s > tests/%s" % (filename, out_filename))
