#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli n;

int main()
{
  while (scanf("%lld", &n) != EOF)
  {
    lli ans = 0;
    for (int i = 3; i <= n; i ++)
      ans += (i - 1) * i;
    printf("%lld\n", ans);
  }
  return(0);
}