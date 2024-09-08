#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  MAKE THE TUTORIAL FOR THIS ONE
  AND ALSO PUT THAT NICE CHOOSE ON YOUR MATH TEMPLATE
*/

const int maxN = 1e6 + 2; int n;
const lli mod = 2;
char a[maxN];

lli fat[maxN];
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli nn, lli k)
{
  if (nn < k) return 0;
  if (nn < mod) return fat[nn] * inv(fat[k] * fat[nn - k] % mod) % mod;
  lli ans = 1;
  while (nn || k)
  {
    lli nnn = nn % mod, kk = k % mod;
    nn /= mod, k /= mod;
    ans = ans * choose(nnn, kk) % mod;
  }
  return ans;
}
/*
1
0
2
0
2
2
2
1
*/
int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxN; i++)
    fat[i] = i * fat[i - 1] % mod;

  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", a);
    DEBUG {
      int x[n][n];
      for (int j = 0; j < n; j++)
      {
        printf("%c%c", a[j], j < n - 1 ? ' ' : '\n');
        x[0][j] = a[j] - '0';
      }

      for (int i = 1; i < n; i++)
      {
        for (int j = 0; j < i; j++) printf(" ");
        for (int j = 0; j < n - i; j++)
        {
          x[i][j] = abs(x[i - 1][j] - x[i - 1][j + 1]);
          printf("%d%c", x[i][j], j < n - i - 1 ? ' ' : '\n');
        }
      }
      printf("----------\n");
    }

    int x[n]; for (int i = 0; i < n; i++) x[i] = (a[i] - '1');

    bool hasOne = false;
    lli answer = 0;
    for (int i = 0; i < n; i++)
      if (x[i] == 1)
        answer = (answer + choose(n - 1, i)) % mod, hasOne = true;

    if (hasOne)
      printf("%lld\n", answer & 1LL);
    else
    {
      answer = 0;
      for (int i = 0; i < n; i++)
        if (x[i] == 2)
          answer = (answer + choose(n - 1, i)) % mod;
      printf("%lld\n", 2LL * (answer & 1LL));
    }
  }
  return 0;
}