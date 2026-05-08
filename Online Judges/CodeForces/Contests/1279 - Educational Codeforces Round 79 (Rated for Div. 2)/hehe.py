from random import randint


options = [chr(i) for i in range(ord('a'), ord('z') + 1)] + [chr(i) for i in range(ord('A'), ord('Z') + 1)]


n = int(1e6)
print(n, 10, 2)
s = ''.join([options[randint(0, len(options) - 1)] for _ in range(n)])
print(s)