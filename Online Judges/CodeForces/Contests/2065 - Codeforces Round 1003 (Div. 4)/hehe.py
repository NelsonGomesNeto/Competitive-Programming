from math import gcd

def lcm(a, b):
    return a * b // gcd(a, b)

print(lcm(3, 3))