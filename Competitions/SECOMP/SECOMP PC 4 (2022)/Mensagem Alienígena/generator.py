import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

# shutil.rmtree("tests", ignore_errors=True)
# os.mkdir("tests")

# (c * x + y) % m = o
# c * x % m + y % m = o
# c * x % m = o - y % m
# c = (o - y % m) * inv(x) % m
mod = 127

def inv(x: int) -> int:
    return pow(x, mod - 2, mod)

def encode(message: str, x: int, y: int) -> str:
    inv_x = inv(x)
    return ''.join(map(lambda c: chr((ord(c) - y + mod) * inv_x % mod), message))
    # return ''.join([(c - y + mod) * inv_x % mod for c in message])

def decode(message: str, x: int, y: int) -> str:
    return ''.join(map(lambda c: chr((ord(c) * x + y) % mod), message))

# test_cases = int(input())
test_cases = 4
for t in range(4, test_cases + 1):
    # f = open("tests/%d.in" % t, "w", encoding='ascii')
    f = open("tests/example_%d.in" % t, "w", encoding='ascii')

    n = randint(1, int(1e5))
    x, y = randint(1, 1000), randint(0, 1000)
    # s = ''.join(map(lambda _: chr(randint(ord('!'), ord('~'))), range(n)))
    s = [
        'paz e amor',
        'The quick brown fox jumps over the lazy dog',
        '42',
        'oi sumido'
    ][t - 1]
    x = 1
    y = 0
    n = len(s)
    encoded_s = encode(s, x, y)
    decoded_s = decode(encoded_s, x, y)
    # print("encode(%s) = " % s, encoded_s, "| decode(%s) = " % encoded_s, decoded_s)
    assert(decoded_s == s)

    print(n, x, y, file=f)
    print(*map(ord, encoded_s), file=f)

    f.close()

for filename in os.listdir("tests"):
    if ".in" in filename:
        out_filename = filename.replace(".in", ".out")
        os.system("./test < tests/%s > tests/%s" % (filename, out_filename))
    # os.system("cat %d.in" % t)
    # os.system("cat %d.out" % t)