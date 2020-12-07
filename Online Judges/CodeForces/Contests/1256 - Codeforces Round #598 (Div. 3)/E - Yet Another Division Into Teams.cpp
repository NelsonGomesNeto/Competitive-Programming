#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that you may only make teams of size 3, 4 and 5. Any team with 6 or
  more members can be splitted into two teams, and will be cheaper.

  Sort everybody, but keep track of their id, since you need to make the teams afterwards.
  Now you can solve the problem using dynamic programming:
    State: i [0 : 2e5], the i-th person you're processing
    Value: the best possible assignment from i to n
    Actions: you can group the i-th person with 2, 3 or 4 more people
      Try them all, save the best answer and also save the best choice
      Remember that you MUST make groups of at least 3 people
*/

const int maxN = 2e5; int n;
const lli inf = 1e16;
pair<lli, int> a[maxN];

lli memo[maxN]; int choice[maxN];
lli solve(int i = 0)
{
  if (i == n) return 0;
  if (memo[i] == -1)
  {
    lli ans = inf;
    for (int j = 3; j <= 5 && i + j <= n; j ++)
    {
      lli ret = solve(i + j) + a[i + j - 1].first - a[i].first;
      if (ret < ans)
        ans = ret, choice[i] = j;
    }
    memo[i] = ans;
  }
  return memo[i];
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i].first);
      a[i].second = i;
    }
    sort(a, a+n);

    memset(memo, -1, sizeof(memo));
    lli ret = solve();
    int ans[n], t = 0;
    for (int i = 0; i < n; t ++)
    {
      for (int j = 0; j < choice[i]; j ++)
        ans[a[i + j].second] = t;
      i += choice[i];
    }
    printf("%lld %d\n", ret, t);
    for (int i = 0; i < n; i ++)
      printf("%d%c", ans[i] + 1, i < n - 1 ? ' ' : '\n');
  }

  return 0;
}
