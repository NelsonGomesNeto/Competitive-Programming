#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
merge parentHeavyPath and parentVertex
*/

const int maxN = 1e4; int n;
int edgeCost[maxN];
map<int, int> edgeIndex[maxN];
vector<int> tree[maxN];

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{max(value, other.value)};
  }
};
const Data nil = Data{(int)-1e9};
template<class T>
struct Segtree
{
  int size;
  vector<T> data, st;
  Segtree(int size) : size(size)
  {
    data.resize(size);
    st.resize(4*size);
  }
  Segtree(vector<T> &data) : size(data.size()), data(data)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int pos, T value) { update(pos, value, 1, 0, size - 1); }
  void build(int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int pos, T value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};

int subtreeSize[maxN], level[maxN], parent[maxN];
int heavyPath[maxN], position[maxN];
int edgeHeavyPath[maxN], edgePosition[maxN];
vector<vector<int>> heavyPaths;
vector<Segtree<Data>> segtrees;

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
void buildHeavyPaths(int u = 0, int prv = -1, int currIndex = 0)
{
  if (heavyPaths.empty()) heavyPaths.push_back(vector<int>());
  heavyPaths[currIndex].push_back(u);

  for (int v: tree[u])
    if (v != prv)
    {
      if (2*subtreeSize[v] >= subtreeSize[u]) // heavy-edge
        buildHeavyPaths(v, u, currIndex);
      else // light-edge
      {
        heavyPaths.push_back(vector<int>());
        buildHeavyPaths(v, u, heavyPaths.size() - 1);
      }
    }
}
Data query(int u, int v)
{
  Data ans = nil;
  for (; heavyPath[u] != heavyPath[v]; u = parent[heavyPaths[heavyPath[u]][0]])
  {
    if (level[heavyPaths[heavyPath[u]][0]] < level[heavyPaths[heavyPath[v]][0]]) swap(u, v);
    ans = ans + segtrees[heavyPath[u]].query(0, position[u]);
    int head = heavyPaths[heavyPath[u]][0];
    ans = ans + Data{edgeCost[edgeIndex[head][parent[head]]]}; // Since this light-edge doesn't belong to any heavyPath (segtree)
    DEBUG printf("\t%d %d\n", u, v);
  }
  if (level[u] < level[v]) swap(u, v);
  return ans + segtrees[heavyPath[u]].query(position[v], position[u]);
}
void update(int i, Data newValue)
{
  edgeCost[i] = newValue.value;
  if (edgePosition[i] != -1)
    segtrees[edgeHeavyPath[i]].update(edgePosition[i], newValue);
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    while (t--)
    {
      scanf("%d", &n);
      segtrees.clear(), heavyPaths.clear();
      for (int i = 0; i < n; i++) tree[i].clear(), edgeIndex[i].clear();
      memset(edgePosition, -1, sizeof(edgePosition));
      memset(position, -1, sizeof(position));

      for (int i = 0; i < n - 1; i++)
      {
        int u, v, c; scanf("%d %d %d", &u, &v, &c); u--, v--;
        assert(c >= 0);
        tree[u].push_back(v), tree[v].push_back(u);
        edgeIndex[u][v] = edgeIndex[v][u] = i;
        edgeCost[i] = c;
      }

      hldPrecalc();
      buildHeavyPaths();
      for (int i = 0; i < heavyPaths.size(); i++)
      {
        segtrees.push_back(Segtree<Data>(2*(heavyPaths[i].size() - 1) + 1));
        int at = 0;
        for (int j = 0; j < heavyPaths[i].size() - 1; j++)
        {
          int u = heavyPaths[i][j], v = heavyPaths[i][j + 1];
          heavyPath[u] = heavyPath[v] = edgeHeavyPath[edgeIndex[u][v]] = i;
          position[u] = at, edgePosition[edgeIndex[u][v]] = at + 1, position[v] = at + 2;
          segtrees.back().data[at++] = nil;
          segtrees.back().data[at++] = Data{edgeCost[edgeIndex[u][v]]};
          if (j == heavyPaths[i].size() - 2) segtrees.back().data[at++] = nil;
        }
        if (heavyPaths[i].size() == 1)
          heavyPath[heavyPaths[i][0]] = i, position[heavyPaths[i][0]] = 0, segtrees.back().data[0] = nil;
        segtrees.back().build();
      }

      DEBUG
        for (int i = 0; i < heavyPaths.size(); i++)
        {
          printf("\t");
          for (int j = 0; j < heavyPaths[i].size(); j++)
            printf("%d%c", heavyPaths[i][j] + 1, j < heavyPaths[i].size() - 1 ? ' ' : '\n');
        }

      char op[10];
      while (scanf(" %s", op) && strcmp(op, "DONE"))
      {
        if (!strcmp(op, "QUERY"))
        {
          int u, v; scanf("%d %d", &u, &v); u--, v--;
          assert(u != v);
          printf("%d\n", query(u, v).value);
        }
        else
        {
          int i, c; scanf("%d %d", &i, &c); i--;
          assert(c >= 0);
          update(i, Data{c});
        }
      }
    }
  }
  return 0;
}