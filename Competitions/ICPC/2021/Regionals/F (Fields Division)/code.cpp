#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m;
char ans[maxN + 1];
vector<int> graph[maxN];

bool visited[maxN];
void getBob(int u = n - 2)
{
  if (visited[u]) return;
  visited[u] = true;
  ans[u] = 'B';
  for (int v: graph[u])
    if (v != n - 1)
      getBob(v);
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    ans[n] = '\0';
    for (int i = 0; i < n; ++i)
      graph[i].clear();

    for (int i = 0; i < m; ++i)
    {
      int u, v; scanf("%d %d", &u, &v); --u, --v;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    fill(ans, ans+n, 'A');
    memset(visited, false, sizeof(visited));
    getBob();

    printf("%s\n", ans);
  }
  return 0;
}