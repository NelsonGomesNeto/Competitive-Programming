from random import randint

n = int(2e5)
s = [chr(ord('0') + randint(0, 9)) for i in range(n)]
x = ['T' for i in range(n)]
print(''.join(s))
print(''.join(x))
