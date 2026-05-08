import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o p -std=c++23 -O2")
os.system("g++ naive.cpp -o naive -std=c++23 -O2")

while True:
    with open("debug_in", "w") as f:
        print("hehe", file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
