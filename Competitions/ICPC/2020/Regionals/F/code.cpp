#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e3; int n;
lli a[maxN];

lli memo[maxN][maxN + 1];
lli solve(int k, int i = 0)
{
  if (i == n) return k == 0;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    for (int i = 1; i <= n; i++)
      solve(i);


  }
  return 0;
}