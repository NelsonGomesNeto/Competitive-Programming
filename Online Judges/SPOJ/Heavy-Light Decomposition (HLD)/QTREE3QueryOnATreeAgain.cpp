#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
vector<int> tree[maxN];
bool isBlack[maxN];

int subtreeSize[maxN], level[maxN], parent[maxN];
void hldPrecalc(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, parent[v] = u;
      hldPrecalc(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

vector<vector<int>> heavyPaths;
int heavyPath[maxN], position[maxN];
vector<set<int>> blacks;
void buildHld(int u = 0, int prv = -1, int curr = 0)
{
  if (heavyPaths.empty()) heavyPaths.push_back(vector<int>());
  heavyPaths[curr].push_back(u);

  for (int v: tree[u])
    if (v != prv)
    {
      if (2*subtreeSize[v] >= subtreeSize[u])
        buildHld(v, u, curr);
      else
      {
        heavyPaths.push_back(vector<int>());
        buildHld(v, u, heavyPaths.size() - 1);
      }
    }
}

int query(int u)
{
  int ans = -1;
  while (u != 0)
  {
    if (!blacks[heavyPath[u]].empty() && position[u] >= *blacks[heavyPath[u]].begin())
      ans = heavyPaths[heavyPath[u]][*blacks[heavyPath[u]].begin()];
    u = parent[heavyPaths[heavyPath[u]][0]];
  }
  if (!blacks[heavyPath[u]].empty() && position[u] >= *blacks[heavyPath[u]].begin())
    ans = heavyPaths[heavyPath[u]][*blacks[heavyPath[u]].begin()];
  return ans == -1 ? -1 : ans + 1;
}

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    memset(isBlack, false, sizeof(isBlack));
    for (int i = 0; i < n; i++) tree[i].clear(), heavyPaths.clear(), blacks.clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    hldPrecalc();
    buildHld();
    for (int i = 0; i < heavyPaths.size(); i++)
    {
      blacks.push_back(set<int>());
      int j = 0;
      for (int u: heavyPaths[i])
        heavyPath[u] = i, position[u] = j++;
    }

    while (q--)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      if (op == 0)
      {
        isBlack[u] = !isBlack[u];
        if (isBlack[u]) blacks[heavyPath[u]].insert(position[u]);
        else blacks[heavyPath[u]].erase(position[u]);
      }
      else
      {
        int ans = query(u);
        printf("%d\n", ans);
      }
    }
  }
  return 0;
}