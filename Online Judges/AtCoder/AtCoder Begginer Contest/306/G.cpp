#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxMod = 10;
int n, m;
vector<vector<int>> graph;

bool visited[maxMod][maxN];
bool bfs(const int mod)
{
  for (int i = 0; i < mod; ++i)
    fill(visited[i], visited[i]+n, false);

  queue<pair<int, int>> q;
  for (int v : graph[0])
    q.push(make_pair(v, 1));
  while (!q.empty())
  {
    auto [u, s] = q.front();
    q.pop();
    printf("\t\t%d %d\n", s, u + 1);

    if (visited[s][u]) continue;
    visited[s][u] = true;

    int nextStep = s + 1;
    if (nextStep == mod) nextStep = 0;
    for (int v : graph[u])
      q.push(make_pair(v, nextStep));
  }
  DEBUG {
    printf("mod: %d\n", mod);
    for (int s = 0; s < mod; ++s)
      for (int i = 0; i < n; ++i)
        printf("\tvisited[%d][%d] = %d\n", s, i, visited[s][i]);
  }
  return visited[0][0];
}

int main()
{
  int testCases;
  while (~scanf("%d", &testCases))
  {
    for (int tt = 1; tt <= testCases; ++tt)
    {
      scanf("%d %d", &n, &m);
      graph.clear();
      graph.resize(n);
      for (int i = 0; i < m; ++i)
      {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        graph[u].push_back(v);
      }

      bool can = bfs(10);
      printf("%s\n", vector<string>{"No", "Yes"}[can].c_str());
    }
  }
  return 0;
}
