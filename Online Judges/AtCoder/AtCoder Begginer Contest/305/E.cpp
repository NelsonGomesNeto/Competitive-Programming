#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, m, k;
vector<int> graph[maxN];

struct Guard
{
  int u, h;
  void read()
  {
    scanf("%d %d", &u, &h);
    --u;
  }
};
Guard guards[maxN];

int visitedEnergy[maxN];
void multiStartBfs()
{
  fill(visitedEnergy, visitedEnergy + n, -1);
  priority_queue<pair<int, int>> q;
  for (int i = 0; i < k; ++i)
  {
    visitedEnergy[guards[i].u] = max(visitedEnergy[guards[i].u], guards[i].h);
    q.push(make_pair(guards[i].h, guards[i].u));
  }
  while (!q.empty())
  {
    auto [e, u] = q.top();
    DEBUG printf("\t%d %d\n", u, e);
    q.pop();
    if (e == 0) continue;
    if (visitedEnergy[u] > e) continue;

    for (int v : graph[u])
    {
      if (visitedEnergy[v] >= e - 1) continue;
      visitedEnergy[v] = e - 1;
      q.push(make_pair(e - 1, v));
    }
  }
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    for (int i = 0; i < n; ++i)
      graph[i].clear();
    for (int i = 0; i < m; ++i)
    {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    for (int i = 0; i < k; ++i)
      guards[i].read();

    multiStartBfs();
    vector<int> ans;
    for (int i = 0; i < n; ++i)
      if (visitedEnergy[i] > -1)
        ans.push_back(i);
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i)
      printf("%d%c", ans[i] + 1, i + 1 < ans.size() ? ' ' : '\n');
  }
  return 0;
}
