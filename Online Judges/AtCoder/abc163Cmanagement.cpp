#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> tree[maxN];
int subtree[maxN];

int dfs(int u = 0, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      subtree[u] += 1;
      dfs(v, u);
    }
  return subtree[u];
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(subtree, 0, sizeof(subtree));
    for (int i = 0; i < n; i++)
      tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int p; scanf("%d", &p); p--;
      tree[i].push_back(p), tree[p].push_back(i);
    }

    dfs();

    for (int i = 0; i < n; i++)
      printf("%d\n", subtree[i]);
  }
  return 0;
}