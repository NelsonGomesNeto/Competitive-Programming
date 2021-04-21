#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxAge = 1e5 + 2, maxLog = 17; int n, m;
int age[maxN], parent[maxN];
vector<int> tree[maxN];

struct Query
{
  int host, l, r;
  void read() { scanf("%d %d %d", &host, &l, &r); host--; }
  void print() { printf("%d %d %d\n", host + 1, l, r); }
};
vector<Query> myQueries[maxN];

int level[maxN], ancestor[maxN][maxLog], ancestorMaxAge[maxN][maxLog];
int logn;
void dfsLCA(int u)
{
  for (int v: tree[u])
  {
    level[v] = level[u] + 1, ancestor[v][0] = u, ancestorMaxAge[v][0] = max(age[v], age[u]);
    dfsLCA(v);
  }
}
void buildLCA()
{
  level[0] = ancestor[0][0] = 0, ancestorMaxAge[0][0] = age[0]; dfsLCA(0);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      ancestorMaxAge[u][i] = max(ancestorMaxAge[u][i - 1], ancestorMaxAge[ancestor[u][i - 1]][i - 1]);
      // If you want to add something about the path, like weight:
      // weight[u][i] = combination of weight[u][i - 1] and weight[ancestor[u][i - 1]][i - 1]
    }
}
int bestParent(int u, int r)
{
  for (int i = logn - 1; i >= 0; i--)
    if (ancestorMaxAge[u][i] <= r)
      u = ancestor[u][i];
  return u;
}

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
};
const Data nil = Data{0};

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
      st[i].value += value.value;
      // data[lo].value += value.value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

int ans[maxN];
void dfs(int u = 0)
{
  for (Query &q: myQueries[u])
  {
    segtree.update(q.l, Data{1});
    segtree.update(q.r + 1, Data{-1});
  }

  ans[u] = segtree.query(0, age[u]).value;

  for (int v: tree[u])
    dfs(v);

  for (Query &q: myQueries[u])
  {
    segtree.update(q.l, Data{-1});
    segtree.update(q.r + 1, Data{1});
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  logn = ceil(log2(n));

  for (int i = 0; i < n; i++)
  {
    scanf("%d %d", &age[i], &parent[i]);
    parent[i]--;
    if (i) tree[parent[i]].push_back(i);
  }

  segtree = Segtree<Data>(maxAge, nil);
  for (int i = 0; i < maxAge; i++) segtree.data[i] = nil;
  segtree.build();

  buildLCA();

  for (int i = 0; i < m; i++)
  {
    Query query;
    query.read();
    myQueries[bestParent(query.host, query.r)].push_back(query);
  }

  DEBUG
    for (int i = 0; i < n; i++)
    {
      printf("%d %d\n", i + 1, age[i]);
      for (Query &q: myQueries[i])
      {
        printf("\t");
        q.print();
      }
    }

  dfs();
  for (int i = 0; i < n; i++)
    printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');

  return 0;
}