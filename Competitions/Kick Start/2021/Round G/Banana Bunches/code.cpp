#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e4, maxK = 1e6; int n, k;
const int inf = maxN + 1;
lli b[maxN], acc[maxN + 1];

// 0 didn't start first, 1 first, 2 didn't start second, 3 started second
// map<lli, lli> memo[maxK][4];
// lli solve(int i = 0, int state = 0, int budget = 0)
// {
//   if (budget == k) return 0;
//   if (i >= n || budget > k || state > 3) return inf;
//   if (memo[budget][state].count(i)) return memo[budget][state][i];
//   lli &ans = memo[budget][state][i];

//   if (state & 1)
//     ans = min(1 + solve(i + 1, state, budget + b[i]), solve(i + 1, state + 1, budget));
//   else
//     ans = min(solve(i + 1, state, budget), 1 + solve(i + 1, state + 1, budget + b[i]));

//   return ans;
// }
vector<pair<int, int>> blocks[maxK + 1];
int solve2()
{
  for (int i = 0; i <= k; i++) blocks[i].clear();

  int ans = inf;
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      if (acc[j + 1] - acc[i] <= k)
        blocks[acc[j + 1] - acc[i]].push_back(make_pair(i, j));

  for (auto &[l, r]: blocks[k])
    ans = min(ans, r - l + 1);

  for (int i = 1; i < k; i++)
  {
    if (blocks[k - i].empty()) continue;

    for (auto &[l0, r0]: blocks[i])
    {
      int sz0 = r0 - l0 + 1;
      DEBUG printf("\t%d - %d %d\n", i, l0, r0);
      for (auto it = lower_bound(blocks[k - i].begin(), blocks[k - i].end(), make_pair(r0 + 2, -1)); it != blocks[k - i].end(); it++)
      {
        int l1 = it->first, r1 = it->second;
        assert(l1 > r0 + 1);

        int sz1 = r1 - l1 + 1;
        ans = min(ans, sz0 + sz1);
      }
    }
  }

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%lld", &b[i]);
    for (int i = 0; i < n; i++) acc[i + 1] = acc[i] + b[i];

    // for (int i = 0; i <= k; i++)
    //   for (int j = 0; j < 4; j++)
    //     memo[i][j].clear();

    int ans = solve2();
    if (ans >= inf) ans = -1;
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}
