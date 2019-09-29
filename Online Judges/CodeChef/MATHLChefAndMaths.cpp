#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
const lli mod = 1e9 + 7; lli n;
lli f[maxN], facum[maxN];

int main()
{
  f[0] = facum[0] = 1;
  for (int i = 1; i < maxN; i ++)
  {
    f[i] = (i * f[i - 1]) % mod;
    facum[i] = (f[i] * facum[i - 1]) % mod;
  }
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld", &n);
    printf("%lld\n", facum[n]);
  }
  return 0;
}