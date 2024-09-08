#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
int a[maxN];

bool inCycle[maxN];
int visited[maxN];
void dfs(int u)
{
  if (visited[u])
  {
    if (visited[u] == 1)
      inCycle[u] = true;
    return;
  }

  visited[u] = 1;
  dfs(a[u]);
  visited[u] = 2;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }

    memset(visited, 0, sizeof(visited));
    memset(inCycle, false, sizeof(inCycle));
    for (int i = 0; i < n; ++i)
      dfs(i);

    vector<int> newInCycle;
    for (int i = 0; i < n; ++i)
      if (inCycle[i])
      {
        int u = a[i];
        while (u != i)
        {
          newInCycle.push_back(u);
          u = a[u];
        }
      }
    for (const int i : newInCycle)
      inCycle[i] = true;

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
      DEBUG printf("\t%d %d\n", i + 1, inCycle[i]);
      ans += inCycle[i];
    }
    printf("%d\n", ans);
  }
  return 0;
}
