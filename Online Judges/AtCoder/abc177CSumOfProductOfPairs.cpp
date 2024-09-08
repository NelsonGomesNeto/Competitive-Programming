#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
lli a[maxN], acc[maxN + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      acc[i + 1] = (acc[i] + a[i]) % mod;

    lli ans = 0;
    for (int i = 0; i < n; i++)
      ans = (ans + a[i] * (acc[n] - acc[i + 1] + mod) % mod) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}