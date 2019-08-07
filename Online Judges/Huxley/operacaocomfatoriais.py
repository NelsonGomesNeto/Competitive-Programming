import math
import sys

def main():
    x = 2
    n = 2
    while ((x > 0 & n > 0)):
        x,n = map(int,sys.stdin.readline().split())#, input(" "), float(input())
        soma = 0
        while (n >= 1):
            if (n % 2 == 0):
                soma -= pow(x,(2 * (n - 1))) / math.factorial((2 * (n - 1)) + 1)
            else:
                if (n > 1):
                    soma -= pow(x,(2 * (n - 1))) / math.factorial((2 * (n - 1)) + 1)
                else:
                    soma += x
        n -= 1
        print(soma)
                    
