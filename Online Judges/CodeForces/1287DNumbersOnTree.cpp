#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2000, spacing = 3000; int n;
vector<int> tree[maxN];
int p[maxN], c[maxN], a[maxN], root;

int subtreeSize[maxN];
void calcSubtree(int u = root)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
  {
    calcSubtree(v);
    subtreeSize[u] += subtreeSize[v];
  }
}

set<int> used;
void dfs(int u = root)
{
  int minimum = c[u] + 1;
  for (int i: used)
    if (i <= minimum) minimum ++;
    else break;
  a[u] = minimum;
  used.insert(a[u]);

  for (int v: tree[u])
    dfs(v);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    used.clear();
    for (int i = 0; i < n; i ++) tree[i].clear();
    
    for (int i = 0; i < n; i ++)
    {
      scanf("%d %d", &p[i], &c[i]); p[i] --;
      if (p[i] != -1) tree[p[i]].push_back(i);
      else root = i;
    }
    calcSubtree();

    bool can = true;
    for (int i = 0; i < n; i ++)
      if (c[i] >= subtreeSize[i])
        can = false;
    if (!can) printf("NO\n");
    else
    {
      printf("YES\n");
      dfs();
      for (int i = 0; i < n; i ++)
        printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}