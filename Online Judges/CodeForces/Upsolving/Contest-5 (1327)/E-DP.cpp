#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
const lli mod = 998244353;
lli ans[maxN];

int main()
{
  ans[1] = 10, ans[2] = 180;
  for (int i = 3; i < maxN; i++)
    ans[i] = ans[i - 1] * 9;

  while (scanf("%d", &n) != EOF)
    for (int i = 1; i <= n; i++)
      printf("%lld%c", ans[i], i < n ? ' ' : '\n');
  return 0;
}