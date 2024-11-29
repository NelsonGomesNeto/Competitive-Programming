import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o p -std=c++23")
os.system("g++ Dnaive.cpp -o naive -std=c++23")

while True:
    with open("debug_in", "w") as f:
        n = randint(4, 10)
        print(n, file=f)
        a = [randint(1, n) for _ in range(n)]
        print(*a, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
