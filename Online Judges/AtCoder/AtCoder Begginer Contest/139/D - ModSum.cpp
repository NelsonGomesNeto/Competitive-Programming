#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli apSum(lli a1, lli n, lli q)
{
  return (a1+a1+(n-1)*q)*n / 2LL;
}

int main()
{
  int n; scanf("%d", &n);

  lli ans = apSum(1, n - 1, 1);
  printf("%lld\n", ans);

  return(0);
}