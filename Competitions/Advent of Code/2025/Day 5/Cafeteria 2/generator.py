from random import randint

N = int(1e5)
MAX_A = int(1e12) - 1

cuts = [randint(0, MAX_A - 1) for _ in range(N)]
cuts.sort()
l = 0
for c in cuts:
    print(f"{l}-{c}")
    l = c + 1

# for _ in range(N):
#     l = randint(0, MAX_A)
#     r = randint(l, MAX_A)
#     print(f"{l}-{r}")