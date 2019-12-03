#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN];
int centroidRoot, subtree[maxN];
int getSubtreeSize(int u, int prv = -1)
{
  subtree[u] = 1;
  for (int v: tree[u])
    if(v != prv && !inCentroidTree[v])
      subtree[u] += getSubtreeSize(v, u);
  return subtree[u];
}
int getCentroid(int u, int nodes, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv && !inCentroidTree[v] && subtree[v] > (nodes >> 1))
      return getCentroid(v, nodes, u);
  return u;
}
int centroidDecomposition(int u = 0, int prv = -1)
{
  int centroid = getCentroid(u, getSubtreeSize(u));
  inCentroidTree[centroid] = true;
  for (int v: tree[centroid])
    if (v != prv && !inCentroidTree[v])
    {
      int centroidChild = centroidDecomposition(v, centroid);
      centroidTree[centroid].push_back(centroidChild), centroidTree[centroidChild].push_back(centroid);
    }
  return centroid;
}

char commanders[maxN];
bool bfs()
{
  queue<pair<pair<int, int>, char>> q; q.push({{centroidRoot, -1}, 'A'});
  while (!q.empty())
  {
    int u = q.front().first.first, prv = q.front().first.second;
    char c = q.front().second; q.pop();
    DEBUG printf("\t%d %d %c - %d\n", prv, u, c, (int) centroidTree[u].size());
    commanders[u] = c;
    if (c > 'Z') return false;
    for (int v: centroidTree[u])
      if (v != prv)
        q.push({{v, u}, c + 1});
  }
  return true;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(inCentroidTree, false, sizeof(inCentroidTree));
    for (int i = 0; i < n; i ++)
      tree[i].clear(), centroidTree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v), tree[v].push_back(u);
    }
    centroidRoot = centroidDecomposition();

    bool can = bfs();
    if (!can) printf("Impossible!\n");
    else
      for (int i = 0; i < n; i ++)
        printf("%c%c", commanders[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}