#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3, inf = INT_MAX; int n;
int a[3][maxN];

int memo[maxN][2];
int solve(int i = 0, bool prvAte = false)
{
  if (i == n) return 0;
  if (memo[i][prvAte] == -1)
  {
    int ans = inf;
    if (prvAte) ans = max(a[1][i] + solve(i + 1, true), i + 1 < n ? a[2][i] + solve(i + 1, false) : 0);
    else ans = max(a[0][i] + solve(i + 1, true), i + 1 < n ? a[1][i] + solve(i + 1, false) : 0);
    memo[i][prvAte] = ans;
  }
  return memo[i][prvAte];
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < 3; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%d", &a[i][j]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }

  return 0;
}