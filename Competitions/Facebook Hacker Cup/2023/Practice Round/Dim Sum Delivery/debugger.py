import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o p -std=c++20")
os.system("g++ naive.cpp -o n -std=c++20")

MAX_N = 10

while True:
    f = open("big", "w")
    test_cases = 50000
    print(test_cases, file=f)
    n, m = randint(2, MAX_N), randint(2, MAX_N)
    a, b = randint(1, n - 1), randint(1, m - 1)
    print(n, m, a, b, file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./n < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")