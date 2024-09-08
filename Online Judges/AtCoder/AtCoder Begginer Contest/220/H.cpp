#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n, m;
vector<int> graph[maxN];
bool hasEdge[maxN][maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(hasEdge, false, sizeof(hasEdge));
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v);
      graph[u].push_back(v), graph[v].push_back(u);
      hasEdge[u][v] = hasEdge[v][u] = true;
    }

    
  }
  return 0;
}