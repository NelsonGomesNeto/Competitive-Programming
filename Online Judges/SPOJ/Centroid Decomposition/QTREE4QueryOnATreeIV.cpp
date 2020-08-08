#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  This problem is very similar to QTREE5, where the query is to find the minimum
  distance between v and a white vertex. Since it's minimum, there are some
  simplifications you can do.

  This problem is perfect to truly understand a very important concept of 
  Centroid Decomposition. Suppose the following centroid tree:
    a   The path between any vertex on b's subtree and any vertex on c's subtree
   / \  will have 'a' as it's LCA. This was a property on the original tree
  b   c and it is still present here.

  With that said, this problem can be solved in O(lg^2) updates and O(1) queries.
  The idea uses the following DP:
    memo[u] = max(memo[v in childs(u)], *max pair of distances from two different branches)
      (All that using the Centroid Tree, since that property is guaranteed)
    With this, ans = memo[centroidRoot].
    And for every update, you just need to add or remove that vertex into its parent's
    corresponding distance multiset.

  max pair of distances from two different branches:
    Notice that you can't pick two distances from the same branch, because this it's not
    guaranteed that it is a path.
    Also notice that you may consider u as a "branch" with distance 0. Since it may be better
    to choose the path from a vertex to u.
    Another thing to be considered is that the time in this problem is VERY tight, so be careful.
*/

const int maxN = 1e5; int n;
const int inf = 1e9;
bool isWhite[maxN]; int whites;
struct Edge { int u, cost; };
vector<Edge> tree[maxN];

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN]; int centroidRoot;
int centroidLevel[maxN], centroidParent[maxN], centroidChildIndex[maxN], subtreeSize[maxN];
int getSubtreeSize(int u, int prv = -1)
{
  subtreeSize[u] = 1;
  for (Edge &e: tree[u])
    if (e.u != prv && !inCentroidTree[e.u])
      subtreeSize[u] += getSubtreeSize(e.u, u);
  return subtreeSize[u];
}
int getCentroid(int u, int nodes, int prv = -1)
{
  for (Edge &e: tree[u])
    if (e.u != prv && !inCentroidTree[e.u] && subtreeSize[e.u] > (nodes >> 1))
      return getCentroid(e.u, nodes, u);
  return u;
}
int centroidDecomposition(int u = 0, int prv = -1)
{
  int centroid = getCentroid(u, getSubtreeSize(u));
  inCentroidTree[centroid] = true;
  centroidLevel[centroid] = prv == -1 ? 0 : centroidLevel[prv] + 1;
  for (Edge &e: tree[centroid])
    if (e.u != prv && !inCentroidTree[e.u])
    {
      int centroidChild = centroidDecomposition(e.u, centroid);
      centroidTree[centroid].push_back(centroidChild);
      centroidChildIndex[centroidChild] = centroidTree[centroid].size() - 1;
      centroidParent[centroidChild] = centroid;
    }
  return centroid;
}

int ancestor[maxN][18], level[maxN], dist[maxN], logDP[2*maxN + 1];
void LCAdfs(int u = 0, int prv = -1)
{
  for (Edge &e: tree[u])
    if (e.u != prv)
    {
      int v = e.u;
      level[v] = level[u] + 1, ancestor[v][0] = u, dist[v] = dist[u] + e.cost;
      LCAdfs(v, u);
    }
}
void buildLCA()
{
  level[0] = dist[0] = 0; LCAdfs();
  for (int i = 1; i < 18; i++)
    for (int u = 0; u < n; u++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v) return u;
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i--)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return ancestor[u][0];
}
int distance(int u, int v)
{
  return dist[u] + dist[v] - 2*dist[LCA(u, v)];
}

const int maxCentroidChilds = 25;
multiset<int> distances[maxN][maxCentroidChilds];
int memo[maxN];
void updateDistances(int u, int prv, int prvIndex, int x, bool toAdd)
{
  if (u == -1) return;
  DEBUG printf("\tupdating %d %d %d | %d - %d | %d\n", u + 1, prv + 1, x + 1, toAdd, distance(u, x), (int)distances[u][prvIndex].size());

  if (toAdd) distances[u][prvIndex].insert(distance(u, x));
  else distances[u][prvIndex].erase(distances[u][prvIndex].find(distance(u, x)));

  memo[u] = 0;
  int a = -inf, b = -inf;
  for (int i = 0; i < centroidTree[u].size(); i++)
  {
    int v = centroidTree[u][i];
    if (centroidParent[u] != v)
    {
      memo[u] = max(memo[u], memo[v]);
      if (!distances[u][i].empty())
      {
        int value = *distances[u][i].rbegin();
        if (value >= a)
        {
          b = a;
          a = value;
        }
        else if (value >= b)
          b = value;
      }
    }
  }
  if (b != -inf)
    memo[u] = max(memo[u], a + (isWhite[u] ? max(0, b) : b));
  else if (a != -inf && isWhite[u])
    memo[u] = max(memo[u], a);

  updateDistances(centroidParent[u], u, centroidChildIndex[u], x, toAdd);
}

void printSpaces(int spaces) { while (spaces --) printf("   "); }
void printTree(vector<int> t[], int u, int prv = -1, int depth = 0)
{
  printSpaces(depth);
  printf("%d\n", u + 1);
  for (int v: t[u])
    if (v != prv)
      printTree(t, v, u, depth + 1);
}

void lol(int u = centroidRoot, int prv = -1)
{
  for (int v: centroidTree[u])
    if (v != prv)
      lol(v, u);
  updateDistances(u, u, maxCentroidChilds - 1, u, true);
}

int main()
{
  logDP[1] = 0; for (int i = 2; i <= 2*maxN; i ++) logDP[i] = logDP[i >> 1] + 1;

  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    memset(inCentroidTree, false, sizeof(inCentroidTree));
    for (int i = 0; i < n; i++)
    {
      tree[i].clear(), centroidTree[i].clear();
      centroidParent[i] = -1, isWhite[i] = true;
      for (int j = 0; j < maxCentroidChilds; j++) distances[i][j].clear();
    }

    for (int i = 1; i < n; i++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c); u--, v--;
      tree[u].push_back({v, c}), tree[v].push_back({u, c});
    }

    buildLCA();
    centroidParent[centroidRoot = centroidDecomposition()] = -1;
    DEBUG printTree(centroidTree, centroidRoot);

    whites = n;

    // for (int i = 0; i < n; i++)
    //   updateDistances(i, i, maxCentroidChilds - 1, i, isWhite[i] = true);
    lol();

    int q; scanf("%d", &q);
    while (q--)
    {
      char op; scanf(" %c", &op);
      if (op == 'A')
      {
        if (whites == 0) printf("They have disappeared.\n");
        else printf("%d\n", memo[centroidRoot]);
      }
      else
      {
        int u; scanf("%d", &u); u--;
        isWhite[u] = !isWhite[u];
        whites += isWhite[u] ? 1 : -1;
        updateDistances(u, u, maxCentroidChilds - 1, u, isWhite[u]);
      }
    }
  }
  return 0;
}