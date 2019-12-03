#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN]; int centroidRoot;
int centroidLevel[maxN], subtree[maxN];
int getSubtreeSize(int u, int prv = -1)
{
  subtree[u] = 1;
  for (int v: tree[u])
    if (v != prv && !inCentroidTree[v])
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
  centroidLevel[centroid] = prv == -1 ? 0 : centroidLevel[prv] + 1;
  for (int v: tree[centroid])
    if (v != prv && !inCentroidTree[v])
    {
      int centroidChild = centroidDecomposition(v, centroid);
      centroidTree[centroid].push_back(centroidChild), centroidTree[centroidChild].push_back(centroid);
    }
  return centroid;
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

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i ++)
  {
    int u, v; scanf("%d %d", &u, &v);
    tree[u].push_back(v), tree[v].push_back(u);
  }
  printTree(tree, 0);

  centroidRoot = centroidDecomposition();
  printf("Centroid root: %d\n", centroidRoot + 1);
  printTree(centroidTree, centroidRoot);

  return 0;
}