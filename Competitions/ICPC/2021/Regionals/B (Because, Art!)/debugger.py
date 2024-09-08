import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ naive.cpp -o bug -std=c++17")

while True:
    test_file = open("big", "w")
    n = 4
    f = [randint(-10, 10) for i in range(n)]
    c = [randint(-10, 10) for i in range(n)]
    f.sort()
    c.sort()
    print(n, file=test_file)
    print(*f, file=test_file)
    print(*c, file=test_file)
    test_file.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")