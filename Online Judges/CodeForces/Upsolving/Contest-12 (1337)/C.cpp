#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
int done[maxN], dist[maxN], fromLeaf[maxN]; lli sumBelow[maxN];
vector<int> tree[maxN]; int parent[maxN];
priority_queue<pair<lli, int>> pq;

int dfs(int u = 0, int prv = -1, int depth = 0)
{
  dist[u] = depth, fromLeaf[u] = 1;
  bool isLeaf = true;
  for (int v: tree[u])
    if (v != prv)
    {
      parent[v] = u;
      isLeaf = false;
      fromLeaf[u] += dfs(v, u, depth + 1);
    }
  if (isLeaf)
    pq.push({depth, u});
  return fromLeaf[u];
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    while (!pq.empty()) pq.pop();
    memset(done, 0, sizeof(done));
    memset(fromLeaf, 0, sizeof(fromLeaf));
    memset(dist, 0, sizeof(dist));
    memset(sumBelow, 0, sizeof(sumBelow));

    for (int i = 0; i < n - 1; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs();
    lli ans = 0;
    for (int i = 0; i < k; i++)
    {
      lli d = pq.top().first; int u = pq.top().second; pq.pop();
      sumBelow[u] += d;
      if (u != 0)
      {
        sumBelow[parent[u]] += sumBelow[u], done[parent[u]]++;
        if (done[parent[u]] == tree[parent[u]].size() - (parent[u] != 0))
        {
          lli wouldAdd = (lli)dist[parent[u]] * fromLeaf[parent[u]] - sumBelow[parent[u]];
          DEBUG printf("\t\t%d %d %d | %lld | %lld\n", u + 1, parent[u] + 1, fromLeaf[parent[u]], sumBelow[parent[u]], wouldAdd);
          pq.push({wouldAdd, parent[u]});
        }
      }

      DEBUG printf("\t%d %lld\n", u + 1, d);
      ans += d;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
