#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
bool isWhite[maxN];
int parent[maxN];
int white[maxN], black[maxN], subtreeSize[maxN];
vector<int> tree[maxN];

void dfs(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      parent[v] = u;
      dfs(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

int query(int u)
{
  int v = u;
  while (parent[v] != -1 && isWhite[parent[v]] == isWhite[u])
    v = parent[v];
  return isWhite[u] ? white[v] : black[v];
}
void applyDelta(int v, int u, bool rem)
{
  if (rem)
  {
    if (isWhite[u])
      white[v] -= white[u];
    else
      black[v] -= black[u];
  }
  else
  {
    if (isWhite[u])
      white[v] += white[u];
    else
      black[v] += black[u];
  }
}
void update(int u)
{
  if (isWhite[u]) black[u]++;
  else white[u]++;
  // printf("\tudpating %d %d | b: %d, w: %d\n", u + 1, isWhite[u], black[u], white[u]);

  int v = u;
  while (parent[v] != -1 && isWhite[parent[v]] == isWhite[u])
  {
    v = parent[v];
    applyDelta(v, u, true);
  }
  if (parent[v] != -1) applyDelta(parent[v], u, true);
  DEBUG printf("\tupdating %d from %d: %d\n", u + 1, isWhite[u], parent[v] + 1);

  isWhite[u] = !isWhite[u];

  v = u;
  while (parent[v] != -1 && isWhite[parent[v]] == isWhite[u])
  {
    v = parent[v];
    applyDelta(v, u, false);
  }
  if (parent[v] != -1) applyDelta(parent[v], u, false);
  DEBUG printf("\tupdating %d to %d: %d\n", u + 1, isWhite[u], parent[v] + 1);

  if (isWhite[u]) black[u]--;
  else white[u]--;
}

int main()
{
  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (tt++)
    {
      printf("\n");
      memset(isWhite, false, sizeof(isWhite));
      for (int i = 0; i < n; i++) tree[i].clear();
    }

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs();
    parent[0] = -1;
    for (int i = 0; i < n; i++)
      black[i] = subtreeSize[i], white[i] = 0;

    DEBUG {
      for (int u = 0; u < n; u++)
        printf("\t\t%d - b: %d, w: %d\n", u + 1, black[u], white[u]);
    }

    scanf("%d", &q);
    while (q--)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      if (op) update(u);
      else printf("%d\n", query(u));

      if (op == 1)
        DEBUG {
          printf("done: %d %d\n", op, u + 1);
          for (int u = 0; u < n; u++)
            printf("\t\t%d - b: %d, w: %d\n", u + 1, black[u], white[u]);
        }
    }
  }
  return 0;
}