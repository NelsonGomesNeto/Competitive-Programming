#include <bits/stdc++.h>
/*
any number can be represented as a sum of powers of 10:
542 == 5*10^2 + 4*10^1 + 2*10^0
542 % mod == (5*(10^2 % mod) + 4*(10^1 % mod) + 2*(10^0 % mod)) % mod
generalizing:

x % mod = (sum (i from 0 to log10(x)) (digit(x, i) * 10^i % mod) ) % mod
  digits are from right to left
*/

int modExp(int x, int y, int mod)
{
  if (!y) return(1);
  int ret = modExp(x, y >> 1, mod);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

int bigmod(char number[], int mod)
{
  int end = strlen(number), rem = 0;
  for (int i = end - 1, p = 0; i >= 0; i --, p ++)
    rem = (rem + (number[i] - '0') * modExp(10, p, mod)) % mod;
  return(rem);
}

int main()
{
  char number[(int) 1e5 + 1]; int mod;
  while (scanf("%s %d", number, &mod) != EOF)
  {
    printf("%d\n", bigmod(number, mod));
    getchar();
  }
  return(0);
}
