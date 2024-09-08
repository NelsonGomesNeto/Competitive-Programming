import os
from random import randint
from filecmp import cmp

os.system("g++ B.cpp -o btest -std=c++17")
os.system("g++ 'B - bug.cpp' -o bbug -std=c++17")

while True:
    f = open("bbig", "w")

    minimum, maximum = 1, 20
    t = 10000
    print(t, file=f)

    for _ in range(t):
        A, B, n = randint(minimum, maximum), randint(minimum, maximum), randint(3, 5)
        print(A, B, n, file=f)
        a = [randint(minimum, maximum) for i in range(n)]
        print(*a, file=f)
        b = [randint(minimum, maximum) for i in range(n)]
        print(*b, file=f)

    f.close()

    os.system("./btest < bbig > bmy")
    os.system("./bbug < bbig > bcor")
    if not cmp("bmy", "bcor"):
        break
    print("Passou")