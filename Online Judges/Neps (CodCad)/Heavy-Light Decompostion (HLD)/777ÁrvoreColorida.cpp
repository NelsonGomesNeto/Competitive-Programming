#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxX = 50; int n, q;
vector<int> tree[maxN];

struct Data
{
  lli colors;
  Data(int c = -1)
  {
    colors = 0;
    if (c != -1) colors = 1LL << c;
  }
  Data operator+(const Data &other)
  {
    Data ans = Data();
    ans.colors = this->colors | other.colors;
    return ans;
  }
  int countDiff()
  {
    int ans = 0;
    for (int i = 0; i < maxX; i++) ans += (colors >> i) & 1;
    return ans;
  }
};
const Data nil = Data();
struct Segtree
{
  int size;
  vector<Data> data;
  vector<Data> st;

  Segtree(int size) : size(size)
  {
    data.resize(size);
    st.resize(4*size);
  }

  void build() { build(1, 0, size - 1); }
  void update(int pos, Data &value) { update(pos, value, 1, 0, size - 1); }
  Data query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
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
  void update(int pos, Data &value, int i, int lo, int hi)
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
  Data query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
};
Data vcolor[maxN];

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
vector<Segtree> segtrees;
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

void update(int u, Data x)
{
  vcolor[u] = x;
  segtrees[heavyPath[u]].update(position[u], x);
}
Data query(int u, int v)
{
  Data ans = nil;
  for (; heavyPath[u] != heavyPath[v]; u = parent[heavyPaths[heavyPath[u]][0]])
  {
    if (level[heavyPaths[heavyPath[u]][0]] < level[heavyPaths[heavyPath[v]][0]]) swap(u, v);
    ans = ans + segtrees[heavyPath[u]].query(0, position[u]);
  }
  if (level[u] < level[v]) swap(u, v);
  return ans + segtrees[heavyPath[u]].query(position[v], position[u]);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    heavyPaths.clear(), segtrees.clear();
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 0; i < n; i++)
    {
      int c; scanf("%d", &c); c--;
      vcolor[i] = Data(c);
    }

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    hldPrecalc();
    buildHld();
    for (int i = 0; i < heavyPaths.size(); i++)
    {
      segtrees.push_back(Segtree(heavyPaths[i].size()));
      int j = 0;
      for (int u: heavyPaths[i])
      {
        heavyPath[u] = i, position[u] = j;
        segtrees[i].data[j++] = vcolor[u];
      }
      segtrees[i].build();
    }

    scanf("%d", &q);
    while (q--)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int u, x; scanf("%d %d", &u, &x); u--, x--;
        update(u, Data(x));
      }
      else
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        printf("%d\n", query(u, v).countDiff());
      }
    }
  }
  return 0;
}