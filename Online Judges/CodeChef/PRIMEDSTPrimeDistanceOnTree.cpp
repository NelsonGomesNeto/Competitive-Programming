#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e4 + 1, maxLog = 16; int n;
vector<int> tree[maxN];
void addEdge(vector<int> g[], int u, int v)
{
  g[u].push_back(v), g[v].push_back(u);
}

bool notPrime[maxN];
vector<int> primes;
void sieve()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i * primes[j] < maxN; j ++)
    {
      notPrime[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }
}

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN];
int subtree[maxN], centroidLevel[maxN], cntDists[maxN], centroidRoot;
ldouble ans;
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
      addEdge(centroidTree, centroid, centroidChild);
    }
  return centroid;
}

bool done[maxN];
void fillDists(int u, int add, int d, int prv = -1)
{
  cntDists[d] += add;
  for (int v: tree[u])
    if (v != prv && !done[v])
      fillDists(v, add, d + 1, u);
}
ldouble cntPrimeDists(int u, int prv = -1, int d = 1)
{
  ldouble res = 0;
  for (int &p: primes)
  {
    if (p - d < 0) continue;
    if (!cntDists[p - d]) break;
    res += cntDists[p - d];
    if (p - d == 0) res += cntDists[p - d];
  }
  for (int v: tree[u])
    if (v != prv && !done[v])
      res += cntPrimeDists(v, u, d + 1);
  return res;
}
void dfs(int u = centroidRoot, int prv = -1)
{
  memset(cntDists, 0, sizeof(cntDists));
  fillDists(u, 1, 0);
  done[u] = true;
  for (int v: tree[u])
    if (!done[v])
    {
      fillDists(v, -1, 1);
      ans += cntPrimeDists(v);
      fillDists(v, 1, 1);
    }
  for (int v: centroidTree[u])
    if (v != prv)
      dfs(v, u);
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
  sieve();

  while (scanf("%d", &n) != EOF)
  {
    memset(inCentroidTree, false, sizeof(inCentroidTree));
    memset(done, false, sizeof(done));
    for (int i = 0; i < n; i ++) tree[i].clear(), centroidTree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      addEdge(tree, u, v);
    }
    centroidRoot = centroidDecomposition();

    ans = 0;
    dfs();
    ans /= (ldouble) n * (n - 1);
    printf("%.15Lf\n", ans);
  }
  return 0;
}