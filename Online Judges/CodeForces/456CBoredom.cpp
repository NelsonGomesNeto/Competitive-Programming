#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxA = 1e5; int n;
int a[maxN], c[maxA + 1];

lli memo[maxA + 1];
lli solve(int i)
{
  if (i >= maxA + 1) return(0);
  if (memo[i] == -1)
  {
    lli ans = solve(i + 1);
    ans = max(ans, solve(i + 2) + (lli) i*c[i]);
    memo[i] = ans;
  }
  return(memo[i]);
}

lli iterativeSolve()
{
  memo[0] = 0, memo[1] = 1*c[1];
  for (int i = 2; i <= maxA; i ++)
    memo[i] = max(memo[i - 1], memo[i - 2] + (lli) i*c[i]);
  return(memo[maxA]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    c[a[i]] ++;
  }

  memset(memo, -1, sizeof(memo));
  // lli ans = solve(0);
  lli ans = iterativeSolve();
  printf("%lld\n", ans);

  return(0);
}