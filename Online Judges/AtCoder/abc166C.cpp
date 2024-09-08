#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    bool good[n]; memset(good, false, sizeof(good));
    int h[n]; for (int i = 0; i < n; i++) scanf("%d", &h[i]);
    vector<int> graph[n];
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
    {
      good[i] = true;
      for (int j: graph[i])
        if (h[j] >= h[i])
          good[i] = false;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      if (good[i]) printf("\t%d\n", i + 1);
      ans += good[i];
    }
    printf("%d\n", ans);
  }
  return 0;
}