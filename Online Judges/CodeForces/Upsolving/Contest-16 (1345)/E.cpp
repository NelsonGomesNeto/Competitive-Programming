#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
vector<int> graph[maxN];

int color[maxN];
bool hasCycle(int u = 0)
{
  if (color[u]) return color[u] == 1;
  color[u] = 1;
  for (int v: graph[u])
    if (hasCycle(v))
      return true;
  color[u] = 2;
  return false;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    string ans = "";
    for (int i = 0; i < n; i++)
      graph[i].clear(), ans += "A", color[i] = 0;
    int as = n;
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      if (ans[v] == 'A') as--;
      ans[v] = 'E';
      graph[u].push_back(v);
    }

    bool can = true;
    for (int i = 0; i < n; i++)
      if (!color[i] && hasCycle(i))
        can = false;

    if (!can) printf("-1\n");
    else printf("%d\n%s\n", as, ans.c_str());
  }
  return 0;
}
