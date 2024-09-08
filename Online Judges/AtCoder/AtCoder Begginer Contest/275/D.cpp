#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

map<lli, lli> memo;
lli f(lli n)
{
  if (memo.count(n)) return memo[n];
  return memo[n] = n == 0 ? 1 : f(n / 2) + f(n / 3);
}

lli n;

int main()
{
  while (~scanf("%lld", &n))
  {
    lli ans = f(n);
    printf("%lld\n", ans);
  }
  return 0;
}
