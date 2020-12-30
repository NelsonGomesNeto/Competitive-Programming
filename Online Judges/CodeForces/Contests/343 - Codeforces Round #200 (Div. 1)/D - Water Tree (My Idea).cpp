#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int fillTimestamp, emptyTimestamp;
  Data operator+(const Data &other)
  {
    return Data{max(fillTimestamp, other.fillTimestamp), max(emptyTimestamp, other.emptyTimestamp)};
  }
};
const Data nil = Data{-1, -1};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() { }
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
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
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      data[lo] = data[lo] + value;
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};

const int maxN = 5e5; int n, q;
vector<int> tree[maxN];

int subtreeSize[maxN], level[maxN], parent[maxN];
int heavyPath[maxN], position[maxN];
vector<vector<int>> heavyPaths;
Segtree<Data> segtree;

void hldPrecalculations(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, parent[v] = u;
      hldPrecalculations(v, u);
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
    ans = ans + segtree.query(position[heavyPaths[heavyPath[u]][0]], position[u]);
  }
  if (level[u] < level[v]) swap(u, v);
  return ans + segtree.query(position[v], position[u]);
}
void update(int u, Data newValue)
{
  segtree.update(position[u], newValue);
}
void updatePath(int u, int v, Data newValue)
{
  update(u, newValue);
  while (heavyPath[u] != heavyPath[v])
  {
    u = parent[heavyPaths[heavyPath[u]][0]];
    segtree.update(position[u], newValue);
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    heavyPaths.clear();
    hldPrecalculations();
    buildHeavyPaths();
    // Build segtree
    segtree = Segtree(n, nil);
    for (int i = 0, j = 0; i < heavyPaths.size(); i++)
    {
      for (int u: heavyPaths[i])
      {
        heavyPath[u] = i, position[u] = j;
        segtree.data[j++] = nil;
      }
    }
    segtree.build();

    DEBUG {
      printf("Heavy Paths:\n");
      for (int i = 0; i < heavyPaths.size(); i++)
      {
        printf("\t");
        for (int j = 0; j < heavyPaths[i].size(); j++)
          printf("%d%c", heavyPaths[i][j], j < heavyPaths[i].size() - 1 ? ' ' : '\n');
      }
      printf("\n");
    }

    scanf("%d", &q);
    for (int qq = 1; qq <= q; qq++)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      DEBUG printf("\t%d %d\n", op, u + 1);
      if (op == 1) // to fill
        update(u, Data{qq, -1});
      else if (op == 2) // to empty
        updatePath(u, 0, Data{-1, qq});
      else // is full?
      {
        Data utoroot = query(u, 0);
        Data uchilds = segtree.query(position[u], position[heavyPaths[heavyPath[u]].back()]);

        printf("%d\n", utoroot.fillTimestamp > uchilds.emptyTimestamp);
      }
    }
  }
  return 0;
}