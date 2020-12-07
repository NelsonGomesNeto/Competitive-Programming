#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b;

lli F(lli n)
{
  lli ans = (n & 1LL) ^ ((n & 2LL)>>1LL) ? 1 : 0;
  for (int bit = 1; bit < 60; bit ++)
  {
    lli smallest = 1LL << bit;
    if (smallest > n || !(n & smallest)) continue;
    lli cnt = (n & (smallest - 1)) + 1;
    if (cnt & 1LL) ans |= smallest;
    DEBUG printf("\t%d %lld %lld\n", bit, cnt, ans);
  }
  return ans;
}

int main()
{
  while (scanf("%lld %lld", &a, &b) != EOF)
  {
    lli ans = F(max(0LL, a - 1)) ^ F(b);
    printf("%lld\n", ans);
  }
  return 0;
}