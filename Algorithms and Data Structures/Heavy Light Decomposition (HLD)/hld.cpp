#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLog = 20;
int n;
vector<int> tree[maxN];
int values[maxN];

void printTree(int u = 0, int prv = -1, int depth = 0)
{
  for (int i = 0; i < depth; i++) printf("   ");
  printf("%d\n", u);
  for (int v: tree[u])
    if (v != prv)
      printTree(v, u, depth + 1);
}

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
};
// DON'T FORGET TO DEFINE THE NIL!!!
const Data nil = Data{0};
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
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
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};

int subtreeSize[maxN], level[maxN];
// Each heavy path has it's own segtree
// Each vertex belongs to a single heavy path (segtree)
int vertexHeavyPath[maxN], vertexPos[maxN], parentHeavyPath[maxN], parentHeavyPathVertex[maxN];
vector<vector<int>> heavyPaths;
vector<Segtree<Data>> segtrees;

void hldPrecalculations(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      hldPrecalculations(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}
// It might be much easier to build the heavy paths from bottom up
void buildHeavyPaths(int u = 0, int prv = -1, int currentHeavyPathIndex = 0)
{
  if (heavyPaths.empty()) heavyPaths.push_back(vector<int>());
  heavyPaths[currentHeavyPathIndex].push_back(u);

  for (int v: tree[u])
    if (v != prv && 2*subtreeSize[v] >= subtreeSize[u]) // heavy-edge
      buildHeavyPaths(v, u, currentHeavyPathIndex);

  for (int v: tree[u])
    if (v != prv && 2*subtreeSize[v] < subtreeSize[u]) // light-edge
    {
      int newHeavyPathIndex = heavyPaths.size();
      parentHeavyPath[newHeavyPathIndex] = currentHeavyPathIndex, parentHeavyPathVertex[newHeavyPathIndex] = u;
      heavyPaths.push_back(vector<int>());
      buildHeavyPaths(v, u, newHeavyPathIndex);
    }
}
Data query(int u, int v)
{
  Data ans = nil;
  for (; vertexHeavyPath[u] != vertexHeavyPath[v]; u = parentHeavyPathVertex[vertexHeavyPath[u]])
  {
    if (level[u] < level[v]) swap(u, v);
    ans = ans + segtrees[vertexHeavyPath[u]].query(0, vertexPos[u]);
  }
  if (level[u] < level[v]) swap(u, v);
  return ans + segtrees[vertexHeavyPath[u]].query(vertexPos[v], vertexPos[u]);
}
void update(int u, Data newValue)
{
  values[u] = newValue.value;
  segtrees[vertexHeavyPath[u]].update(vertexPos[u], newValue);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    segtrees.clear(), heavyPaths.clear();
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 0; i < n; i++) scanf("%d", &values[i]);

    for (int i = 0; i < n - 1; i++)
    {
      int u, v; scanf("%d %d", &u, &v);
      tree[u].push_back(v), tree[v].push_back(u);
    }

    printf("Tree:\n");
    printTree();

    hldPrecalculations();
    buildHeavyPaths();
    // Build segtrees
    for (int i = 0; i < heavyPaths.size(); i++) 
    {
      vector<Data> data;
      for (int u: heavyPaths[i])
      {
        vertexHeavyPath[u] = i, vertexPos[u] = data.size();
        data.push_back(Data{values[u]});
      }
      segtrees.push_back(Segtree(data, nil));
    }

    printf("Heavy Paths:\n");
    for (int i = 0; i < heavyPaths.size(); i++)
    {
      printf("\t");
      for (int j = 0; j < heavyPaths[i].size(); j++)
        printf("%d%c", heavyPaths[i][j], j < heavyPaths[i].size() - 1 ? ' ' : '\n');
    }

    printf("Queries:\n");
    int q; scanf("%d", &q);
    while (q--)
    {
      char op; scanf(" %c", &op);
      if (op == 'Q')
      {
        int u, v; scanf("%d %d", &u, &v);
        printf("\tsumPath(%d, %d) = %d\n", u, v, query(u, v).value);
      }
      else
      {
        int u, value; scanf("%d %d", &u, &value);
        printf("\tupdate node %d's value from %d to %d\n", u, values[u], value);
        update(u, Data{value});
      }
    }
  }
  return 0;
}