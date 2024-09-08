#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
bool isWhite[maxN];
vector<int> tree[maxN];

int query(int uu)
{
  set<int> visited;
  queue<int> q; q.push(uu);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (isWhite[u] != isWhite[uu] || visited.count(u)) continue;
    visited.insert(u);
    for (int v: tree[u])
      q.push(v);
  }
  return visited.size();
}
void update(int u)
{
  isWhite[u] = !isWhite[u];
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

    scanf("%d", &q);
    while (q--)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      if (op) update(u);
      else printf("%d\n", query(u));
    }
  }
  return 0;
}