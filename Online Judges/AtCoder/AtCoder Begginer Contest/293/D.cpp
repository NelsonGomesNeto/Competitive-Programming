#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
const int maxVertices = maxN * 2;
int n, m;

vector<int> graph[maxVertices];
void addEdge(int u, int v)
{
  graph[u].push_back(v);
  graph[v].push_back(u);
}
int getVertex(int u, char c)
{
  return c == 'R' ? u : n + u;
}
int getOtherVertex(int u)
{
  return u < n ? n + u : u - n;
}

int visited[maxVertices];
int startingVertex;
bool dfs(int u, int prv = -1)
{
  if (visited[u]) return visited[u] == 1 && u == startingVertex;
  bool cycled = false;
  visited[u] = 1;
  for (const int v : graph[u])
    if (v != prv)
      cycled |= dfs(v, u);
  visited[u] = 2;
  cycled |= dfs(getOtherVertex(u), u);
  return cycled;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < 2*n; ++i)
      graph[i].clear();
    for (int i = 0; i < m; ++i)
    {
      int u, v; char uc, vc;
      scanf("%d %c %d %c", &u, &uc, &v, &vc);
      --u, --v;
      addEdge(getVertex(u, uc), getVertex(v, vc));
    }

    fill(visited, visited+2*n, 0);
    int groups = 0, cycles = 0;
    for (int i = 0; i < n; ++i)
      if (!visited[i])
      {
        startingVertex = i;
        cycles += dfs(i);
        ++groups;
      }
    printf("%d %d\n", cycles, groups - cycles);
  }
  return 0;
}
