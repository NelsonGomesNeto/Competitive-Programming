import os
from random import randint, shuffle
from filecmp import cmp

os.system("g++ F.cpp -o test -std=c++17")
os.system("g++ 'F - naive.cpp' -o bug -std=c++17")

while True:
    f = open("big", "w")
    test_cases = 5
    print(test_cases, file=f)
    for test_case in range(test_cases):
        n = randint(1, 10)
        print(n, file=f)
        p = list(range(n))
        shuffle(p)
        print(*p, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")