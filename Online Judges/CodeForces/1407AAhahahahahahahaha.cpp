#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[maxN];

int memo[maxN][2][3*maxN];
vector<int> ans;
bool solve(int i = 0, bool even = true, int sum = 0)
{
  if (i == n) return sum == 0;
  if (memo[i][even][sum] != -1) return memo[i][even][sum];

  if (solve(i + 1, !even, sum + (even ? a[i] : -a[i])))
  {
    ans.push_back(a[i]);
    return memo[i][even][sum] = true;
  }
  else if (solve(i + 1, even, sum))
  {
    return memo[i][even][sum] = true;
  }
  return memo[i][even][sum] = false;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

      memset(memo, -1, sizeof(memo));
      ans.clear();
      bool can = solve();
      reverse(ans.begin(), ans.end());

      printf("%d\n", (int)ans.size());
      for (int i = 0; i < ans.size(); i++)
        printf("%d%c", ans[i], i < (int)ans.size() - 1 ? ' ' : '\n');
    }
  return 0;
}
