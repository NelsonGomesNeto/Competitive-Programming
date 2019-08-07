#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, k;
pair<int, int> d[maxN];
int edgeCount[maxN];
vector<int> graph[maxN];

int main()
{
  scanf("%d %d", &n, &k);
  bool can = true; int z = 1;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &d[i].first);
    z -= d[i].first == 0, d[i].second = i;
  }
  if (z != 0) can = false;

  if (!can) printf("-1\n");
  else
  {
    sort(d, d+n);
    for (int i = 1, now = 0; i < n; i ++)
    {
      while (now < i && (edgeCount[d[now].second] == k || d[now].first + 1 < d[i].first)) now ++;
      if (now >= i || d[now].first + 1 != d[i].first) { can = false; break; }
      graph[d[now].second].push_back(d[i].second), edgeCount[d[now].second] ++, edgeCount[d[i].second] ++;
    }
    if (!can) printf("-1\n");
    else
    {
      vector<pair<int, int>> edges;
      for (int i = 0; i < n; i ++)
        for (int j: graph[i])
          edges.push_back({i, j});
      printf("%d\n", (int) edges.size());
      for (auto &e: edges) printf("%d %d\n", e.first + 1, e.second + 1);
    }
  }

  return(0);
}