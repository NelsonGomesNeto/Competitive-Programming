#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9;

const int maxN = 1e3 + 1;
lli choose[maxN][maxN];

int main()
{
  choose[0][0] = 1;
  for (int i = 1; i < maxN; i++)
    for (int j = 0; j <= i; j++)
      choose[i][j] = (choose[i - 1][j] + (j ? choose[i - 1][j - 1] : 0)) % mod;

  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    for (int i = 0; i <= n; i++)
      printf("%lld%c", choose[n][i], i < n ? ' ' : '\n');
  }

  return 0;
}