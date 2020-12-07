from math import sqrt, ceil

r, x, y, nx, ny = map(int, input().split())
print(ceil(sqrt((nx - x)**2 + (ny - y)**2) / (2*r)))
