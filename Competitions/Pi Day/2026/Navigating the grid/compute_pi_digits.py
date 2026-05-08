import decimal
import sys
from decimal import Decimal
from mpmath import mp, nsum
from math import sqrt, factorial

DIGITS = int(1e4)
DEBUG = False

sys.set_int_max_str_digits(DIGITS + 10)


def ChudnovskyMpMath():
    mp.dps = DIGITS + 10
    c = mp.sqrt(10005) / 4270934400
    def kth_term(k):
        a = ((-1)**k) * mp.factorial(6*k) * (545140134*k + 13591409)
        b = mp.factorial(3*k) * (mp.factorial(k)**3) * (640320**(3*k))
        if DEBUG: print("a =", a)
        if DEBUG: print("b =", b)
        return a / b
    s = nsum(kth_term, [0, int(1e3)])
    if DEBUG: print("c =", c)
    if DEBUG: print("s =", s)
    pi = 1 / (c * s)

    print(int(pi * (10**(DIGITS - 1))))


def ChudnovskyDecimal():
    decimal.getcontext().prec = DIGITS + 10
    c = Decimal(10005)**(Decimal(1) / Decimal(2)) / Decimal(4270934400)
    s = Decimal(0)
    if DEBUG: print("c =", c)
    for k in range(int(1e3)):
        a = Decimal(((-1)**k) * factorial(6*k) * (545140134*k + 13591409))
        b = Decimal(factorial(3*k) * (factorial(k)**3) * (640320**(3*k)))
        if DEBUG: print("a =", a)
        if DEBUG: print("b =", b)
        s += a / b
    if DEBUG: print("s =", s)
    pi = 1 / (c * s)

    print(int(pi * (10**(DIGITS - 1))))

ChudnovskyDecimal()