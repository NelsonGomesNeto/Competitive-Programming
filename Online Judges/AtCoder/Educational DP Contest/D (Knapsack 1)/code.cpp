#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxW = 1e5; int n, capacity;
const lli inf = 1e18;
int w[maxN]; lli v[maxN];

lli memo[maxN][maxW];
lli solve(int i = 0, lli curr = capacity)
{
  if (curr < 0) return -inf;
  if (i == n) return 0;
  lli &ans = memo[i][curr];
  if (ans != -1) return ans;

  return ans = max(solve(i + 1, curr - w[i]) + v[i],
                   solve(i + 1, curr));
}

int main()
{
  while (scanf("%d %d", &n, &capacity) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d %lld", &w[i], &v[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}