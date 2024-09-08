#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int b[maxN], p[maxN];
lli dist[maxN], total[maxN];
vector<int> tree[maxN];
int root;

void dfs(vector<pair<lli, int>> &res, int u = root, lli sum = 0)
{
  res.push_back(make_pair(sum, u));
  for (int v: tree[u])
    dfs(res, v, sum + dist[v]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    for (int i = 0; i < n; i++) tree[i].clear();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &b[i]);
      b[i]--;
      if (b[i] != i) tree[b[i]].push_back(i);
      else root = i;
    }
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &p[i]);
      p[i]--;
    }

    if (p[0] != root) printf("-1\n");
    else
    {
      bool can = true;
      fill(dist, dist+n, -1);
      fill(total, total+n, 0);

      dist[root] = 0, total[root] = 0;
      lli accDist = 0;
      for (int i = 1; i < n; i++)
      {
        lli targetDist = accDist + 1;
        lli currSum = total[b[p[i]]];
        if (currSum < 0) can = false;
        dist[p[i]] = targetDist - currSum;
        total[p[i]] = targetDist;
        accDist = targetDist;
      }

      vector<pair<lli, int>> result;
      dfs(result);
      sort(result.begin(), result.end());
      for (int i = 0; i < n; i++)
        if (p[i] != result[i].second)
          can = false;

      if (!can) printf("-1\n");
      else
        for (int i = 0; i < n; i++)
          printf("%lld%c", dist[i], i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}
