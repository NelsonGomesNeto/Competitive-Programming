#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 998244353;
int a[maxN];

lli memo[maxN][10];
lli solve(int target, int i = 0, int curr = a[0])
{
  if (i == n - 1) return curr == target;

  lli &ans = memo[i][curr];
  if (ans != -1) return ans;

  ans = (
    solve(target, i + 1, (curr + a[i + 1]) % 10)
    + solve(target, i + 1, (curr * a[i + 1]) % 10)
  ) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    for (int i = 0; i < 10; i++)
    {
      memset(memo, -1, sizeof(memo));
      lli ans = solve(i);
      printf("%lld\n", ans);
    }
  }
  return 0;
}