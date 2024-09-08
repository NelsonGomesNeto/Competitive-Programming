from random import randint

print(*[randint(1, int(1e5)) for _ in range(int(1e5))])