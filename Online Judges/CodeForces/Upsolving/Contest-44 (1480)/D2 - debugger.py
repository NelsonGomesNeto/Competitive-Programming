import os
from random import randint
from filecmp import cmp

os.system("g++ D2.cpp -o dtest -std=c++17")
os.system("g++ 'D2 - bug.cpp' -o dbug -std=c++17")

while True:
    f = open("dbig", "w")
    n = randint(5, 10)
    print(n, file=f)
    a = [randint(1, n) for i in range(n)]
    print(*a, file=f)
    f.close()

    os.system("./dtest < dbig > dmy")
    os.system("./dbug < dbig > dcor")
    if not cmp("dmy", "dcor"):
        break
    print("Passou")