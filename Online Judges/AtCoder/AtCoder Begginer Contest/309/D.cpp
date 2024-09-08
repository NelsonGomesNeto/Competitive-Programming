#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5, maxM = 3e5;
int n1, n2, m;
vector<int> graph[maxN];

bool visited[maxN];
int biggestDistance(int source)
{
  fill(visited, visited+n1+n2, false);
  queue<pair<int, int>> q;
  q.push(make_pair(source, 0));
  int res = 0;
  while (!q.empty())
  {
    auto [u, d] = q.front();
    q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    res = max(res, d);

    for (int v : graph[u])
      q.push(make_pair(v, d + 1));
  }
  return res;
}

int main()
{
  while (~scanf("%d %d %d", &n1, &n2, &m))
  {
    for (int i = 0; i < m; ++i)
    {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    int ans = biggestDistance(0) + biggestDistance(n1 + n2 - 1) + 1;
    printf("%d\n", ans);
  }
  return 0;
}
