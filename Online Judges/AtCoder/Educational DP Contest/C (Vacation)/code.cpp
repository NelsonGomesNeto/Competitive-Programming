#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const int inf = 1e9;
int a[maxN][3];

int memo[maxN][3];
int solve(int i = 0, int prv = 0)
{
  if (i == n) return 0;
  int &ans = memo[i][prv];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 0; j < 3; j++)
    if (i == 0 || j != prv)
      ans = max(ans, solve(i + 1, j) + a[i][j]);
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < 3; j++)
        scanf("%d", &a[i][j]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}