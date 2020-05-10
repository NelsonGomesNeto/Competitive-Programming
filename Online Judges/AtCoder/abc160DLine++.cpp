#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, inf = 1e6; int n, x, y;
int dist[maxN][maxN], cnt[maxN];

vector<int> graph[maxN];
void addEdge(int u, int v)
{
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void bfs(int source)
{
  queue<int> q; q.push(source);
  dist[source][source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: graph[u])
      if (dist[source][u] + 1 < dist[source][v])
        q.push(v), dist[source][v] = dist[source][u] + 1;
  }
  for (int i = 0; i < n; i++)
    cnt[dist[source][i]]++;
}

int main()
{
  int t = 0;
  while (scanf("%d %d %d", &n, &x, &y) != EOF)
  {
    if (t++) printf("------------\n");
    for (int i = 0; i < n; i++) graph[i].clear();

    for (int i = 0; i < n - 1; i++) addEdge(i, i + 1);
    addEdge(x - 1, y - 1);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        dist[i][j] = inf;
    for (int i = 0; i < n; i++)
      bfs(i);

    for (int i = 1; i < n; i++)
      printf("%d\n", cnt[i] >> 1LL);
  }
  return 0;
}