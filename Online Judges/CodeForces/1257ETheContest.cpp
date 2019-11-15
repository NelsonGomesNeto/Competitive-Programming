#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, inf = 1e6; int k[3], n;
int a[3][maxN];
int belongs[maxN];

int memo[maxN][3];
int solve(int i = 0, int g = 0)
{
  if (i == n) return 0;
  if (memo[i][g] != -1) return memo[i][g];

  int ans = inf;
  for (int gg = g; gg < 3; gg ++)
    ans = min(ans, solve(i + 1, gg) + !(belongs[i] == gg));
  return memo[i][g] = ans;
}

int main()
{
  while (scanf("%d %d %d", &k[0], &k[1], &k[2]) != EOF)
  {
    n = k[0] + k[1] + k[2];
    for (int i = 0; i < 3; i ++)
      for (int j = 0; j < k[i]; j ++)
      {
        scanf("%d", &a[i][j]);
        belongs[a[i][j] - 1] = i;
      }

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
