#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxX = 2e6 + 1; int n;
int a[2*maxN];

vector<int> ss;
vector<pair<int, int>> sums[maxX];
vector<pair<int, int>> choices;
int cnt[maxX];
int dfs(int u, int depth = 0, int idx = 2*n - 1)
{
  DEBUG printf("\t\t%d\n", u);
  // if (memo[u].count({idx, depth}))
  //   return memo[u][{idx, depth}];
  // if (ans != -1) return ans;
  // int &ans = memo[u][{idx, depth}];

  int ans = 0;
  int prvIdx = idx;
  int hehe = 0;
  for (auto &[f, s]: sums[u])
  {
    if (cnt[f] - 1 - (f == s) < 0 || cnt[s] - 1 < 0)
      continue;
    cnt[f]--, cnt[s]--;

    ans = dfs(max(f, s), depth + 1, idx);

    if (depth + 1 + ans == n + 1)
      choices.push_back({f, s});
    cnt[f]++, cnt[s]++;
    break;
  }
  ans++;

  return ans;
}
/*
  1 2 3 4 5 6 7 14 3 11 - 21
  1 2 3 4 5 6 3 11 - 14
  1 2 3 4 5 6 - 11
  1 2 3 4 - 6
  1 3 - 4
  0
*/

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < 2*n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]] = 0;
    }
    sort(a, a+2*n);
    for (int i = 0; i < 2*n; i++)
      cnt[a[i]]++;

    ss.clear();
    for (int i = 0; i < 2*n; i++)
      for (int j = i + 1; j < 2*n; j++)
        ss.push_back(a[i] + a[j]);
    sort(ss.begin(), ss.end());
    ss.resize(distance(ss.begin(), unique(ss.begin(), ss.end())));

    for (int s: ss)
      sums[s].clear();
    for (int i = 0; i < 2*n; i++)
      for (int j = i + 1; j < 2*n; j++)
        sums[a[i] + a[j]].push_back(make_pair(max(a[i], a[j]), min(a[i], a[j])));
    for (int s: ss)
      sort(sums[s].begin(), sums[s].end(), greater<pair<int, int>>());

    int sum = -1;
    set<int> hehe;
    for (int i = 2*n - 2; i >= 0; i--)
      hehe.insert(a[i] + a[2*n - 1]);
    
    for (int u: hehe)
    {
      DEBUG printf("\t%d %d\n", u, dfs(u));
      choices.clear();
      if (dfs(u) == n + 1)
      {
        sum = u;
        break;
      }
    }

    if (sum == -1)
      printf("NO\n");
    else
    {
      printf("YES\n%d\n", sum);
      reverse(choices.begin(), choices.end());
      for (auto &[f, s]: choices)
        printf("%d %d\n", f, s);
    }

    for (int s: ss)
      sums[s].clear();
  }
  return 0;
}