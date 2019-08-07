#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const lli mod = 1e6;
lli n, k, l;
/*
  1| 2|       3|         4|                 5| ...
  1| k| k^2 + l| k^3 + 2kl| k^4 + 3k^2l + l^2| ...
       n
  |k l|
  |1 0|
*/
lli base[2][2], identity[2][2] = {{1, 0}, {0, 1}};

void modMatMult(lli a[2][2], lli b[2][2])
{
  lli res[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < 2; j ++)
      for (int k = 0; k < 2; k ++)
        res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
  memcpy(a, res, sizeof(res));
}

void modMatPow(lli x[2][2], lli y)
{
  lli ans[2][2]; memcpy(ans, identity, sizeof(ans));
  while (y)
  {
    if (y & 1) modMatMult(ans, x);
    modMatMult(x, x), y >>= 1;
  }
  memcpy(x, ans, sizeof(ans));
}

int main()
{
  while (scanf("%lld %lld %lld", &n, &k, &l) != EOF && n)
  {
    n /= 5LL, base[0][0] = k % mod, base[0][1] = l % mod, base[1][0] = 1, base[1][1] = 0;
    modMatPow(base, n);
    printf("%06lld\n", base[0][0]);
    // printf("%6lld - %06lld %6lld %6lld\n", n, ans.ans % mod, ans.mini, ans.bus);
  }
  return(0);
}