#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxVSum = 1e5; const lli maxW = 1e9; int n, capacity;
const lli inf = 1e18;
lli w[maxN]; int v[maxN];

lli memo[maxN][maxVSum + 1];
lli solve(int sum, int i = 0)
{
  if (i == n) return sum <= 0 ? 0 : inf;
  lli &ans = memo[i][sum];
  if (ans != -1) return ans;

  return ans = min(solve(sum - v[i], i + 1) + w[i],
                   solve(sum, i + 1));
}

int bs(int lo = 0, int hi = maxVSum)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    memset(memo, -1, sizeof(memo));
    if (solve(mid) <= capacity) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d", &n, &capacity) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld %d", &w[i], &v[i]);

    int ans = bs();
    printf("%d\n", ans);
  }
  return 0;
}