import os
from random import randint
from filecmp import cmp

os.system("g++-14 'F - New Year and Handle Change.cpp' -o naive -std=c++23 -O2")
os.system("g++-14 Frecover.cpp -o p -std=c++23 -O2")

options = [chr(i) for i in range(ord('a'), ord('z') + 1)] + [chr(i) for i in range(ord('A'), ord('Z') + 1)]

while True:
    with open("debug_in", "w") as f:
        test_cases = int(1e4)
        for test_case in range(test_cases):
            n = randint(2, 10)
            k, l = randint(1, n), randint(1, n)
            print(n, k, l, file=f)
            s = ''.join([options[randint(0, len(options) - 1)] for _ in range(n)])
            print(s, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
