from random import randint
import re

while True:
    try:
        t = int(input())
    except EOFError:
        break

    memo = {}

    class Num:
        def __init__(self, value):
            self.value = value
        def __add__(self, other):
            return Num(self.value + other.value)
        def __xor__(self, other):
            u = (self.value, other.value)
            if not u in memo:
                memo[u] = Num(randint(10**100, 10**200))
            return memo[u]
        def __mul__(self, other):
            return Num(self.value * other.value)
        def __str__(self):
            return str(self.value)
        

    for tt in range(1, t + 1):
        memo = {}

        n = int(input())
        expressions = []
        evals = []
        for i in range(n):
            e = input()
            e = e.replace("#", "^")
            groups = re.findall(r"\d+", e)
            e = re.sub(r"\d+", "?", e)
            for g in groups:
                e = e.replace("?", "Num({})".format(g), 1)
            expressions += [e]
            evals += [eval(e).value]

        mapping = {}
        ans = []
        for i in range(n):
            # print(i, expressions[i], evals[i])
            if not evals[i] in mapping:
                mapping[evals[i]] = len(mapping) + 1
            ans += [mapping[evals[i]]]

        print("Case #%d:" % tt, ' '.join([str(a) for a in ans]))

