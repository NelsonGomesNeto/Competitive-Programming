#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
vector<int> a[maxN];
vector<int> b[maxN];

lli memo[maxN][3];
vector<int> putInTeam(vector<int> team, int i)
{
  for (int j = 0; j < 5; j++)
    team[j] = max(team[j], b[i][j]);
  return team;
}
lli solve(int i = 0, int chosen = 0, vector<int> curr = {0, 0, 0, 0, 0})
{
  if (chosen == 3) return *min_element(curr.begin(), curr.end());
  if (i == n) return 0;

  // if (memo[i].count(curr)) return memo[i][curr];
  lli &ans = memo[i][chosen];
  if (ans != -1)
    return ans;
  ans = max(
    solve(i + 1, chosen, curr),
    solve(i + 1, chosen + 1, putInTeam(curr, i))
  );

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      a[i].clear();
      a[i].resize(5);
      b[i].clear();
      b[i].resize(5);
      for (int j = 0; j < 5; j++)
        scanf("%d", &a[i][j]);
    }

    lli ans = 0;
    vector<int> perm = {0, 1, 2, 3, 4};
    do
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < 5; j++)
          b[i][j] = a[i][perm[j]];
      sort(b, b+n);
      memset(memo, -1, sizeof(memo));
      ans = max(ans, solve());
    }
    while (next_permutation(perm.begin(), perm.end()));

    // for (int i = 0; i < n; i++)
    //   memo[i].clear();
    // memset(memo, -1, sizeof(memo));
    printf("%lld\n", ans);
  }
  return 0;
}