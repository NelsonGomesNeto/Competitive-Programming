import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

def gen_vertex(n: int):
    return (randint(1, n), "RB"[randint(0, 1)])

def gen_edge(n: int):
    return gen_vertex(n), gen_vertex(n)

def vertex_to_str(u: (int, str)):
    return str(u[0]) + " " + u[1]

while True:
    f = open("big", "w")
    n = randint(1, 5)
    m = randint(0, n)
    print(n, m, file=f)
    edges = []
    has_connection = set()
    while len(edges) < m:
        u, v = gen_edge(n)
        while u in has_connection or v in has_connection:
            u, v = gen_edge(n)
        edges.append((u, v))
        has_connection.add(u)
        has_connection.add(v)
    for u, v in edges:
        print(vertex_to_str(u), vertex_to_str(v), file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")