#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101; int n, k; lli m;
lli ans[maxN + 1];

map<int, lli> memo[maxN + 1];
lli solve(int target, int e, int sum = 0, int i = 1)
{
  if (target < 0) return 0;
  if (e < 0) return 0;
  if (target == 0 && e == 0) return 1;
  if (i == n + 1) return 0;
  if (memo[i].count(sum / e)) return memo[i][sum / e];
  lli &res = memo[i][sum / e];
  // if (res != -1) return res;

  res = 0;
  for (int kk = 0; kk <= k; kk++)
    res = (res + solve(target - i * kk, e - kk, sum + i * kk, i + 1)) % m;
  return res;
}

int main()
{
  while (scanf("%d %d %lld", &n, &k, &m) != EOF)
  {
    memset(ans, 0, sizeof(ans));
    for (int x = 1; x <= n; x++)
      for (int e = 1; e <= n * k; e++)
      {
        // memset(memo, -1, sizeof(memo));
          for (int j = 0; j < maxN; j++)
            memo[j].clear();
        lli res = solve(x * e, e);
        DEBUG printf("\tx = %d, e = %d, res = %lld\n", x, e, res);
        ans[x] = (ans[x] + res) % m;
      }

    for (int x = 1; x <= n; x++)
      printf("%lld\n", ans[x]);
  }
  return 0;
}