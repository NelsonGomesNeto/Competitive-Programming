#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int n, m;
vector<int> tree[maxN];
int coverage[maxN];

void dfs(int u = 0, int curr = -1)
{
  curr = max(curr, coverage[u]);
  coverage[u] = curr;
  for (int v : tree[u])
    dfs(v, curr - 1);
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i) tree[i].clear();
    for (int i = 1; i < n; ++i)
    {
      int pi;
      scanf("%d", &pi);
      --pi;
      tree[pi].push_back(i);
    }

    fill(coverage, coverage+n, -1);
    for (int i = 0; i < m; ++i)
    {
      int x, y;
      scanf("%d %d", &x, &y);
      --x;
      coverage[x] = max(coverage[x], y);
    }

    dfs();

    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans += coverage[i] >= 0;
    printf("%d\n", ans);
  }
  return 0;
}
