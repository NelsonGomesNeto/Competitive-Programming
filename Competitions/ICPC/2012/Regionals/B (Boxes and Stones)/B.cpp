#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  B - 1 >= 2^1 stones -> win
  B - 2 >= 2^2 stones -> win
*/
const int maxS = 200, maxN = 100; int s, b;
const lli mod = 1e9 + 7;

lli combinations(lli n, lli k)
{
  printf("C(%lld, %lld)\n", n + k - 1, k - 1);
}

int main()
{
  while (scanf("%d %d", &s, &b) != EOF && s)
  {
    lli ans = 0;
    for (int i = 1; i < b; i ++)
      for (int j = pow(2, i); j <= s; j ++)
        ans = (ans + combinations(b - i, s - j)) % mod;
    printf("%lld - C(%lld, %lld)\n", ans, b + s - 1, s - 1);
  }
  return(0);
}