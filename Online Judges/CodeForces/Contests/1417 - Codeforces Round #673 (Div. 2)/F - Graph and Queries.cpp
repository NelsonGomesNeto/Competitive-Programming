#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  What if, instead of querying for reachables: you queried for maximum in a subtree?

  Subtree? There's no tree...
  Yes, but we can create one:
  Using DSU:
    1 - Insert all edges that weren't removed (merge)
    2 - Iterate through the queries reversed and insert the edges (merge)
    Notice that by doing so, while we're iterating through the revesed queries,
    whenever we reach a query type 1: we know the vertices reachable by u

  But we still can't answer queries of type 1, since it involves and update

  Instead of merging u and v:       w
    create a new node w         |  / \
    merge u into w and v into w | u   v
    This way, w will be in charge of retrieving the answers from it's subtree
    (Notice that DSU path compression is allowed, but small-to-large will break things)

  So, on step 2: when you reach a query of type 1:
    save for that query that the node in charge of the answer is: root(u)

  Now:
  3 - Iterate through the queries normally and query for the maximum in the subtree
    You will also need to update the values in this step

  How to do queries and updates in a subtree: EulerTour
    dfs through the tree:
      add u to a list when you arrive and when you leave
      also save the position you entered and leaved u
    Exemple:
        w   0 1 2 3 4 5
       / \  w u u v v w - is the EulerTour of this tree
      u   v in[w] = 0, in[u] = 1, in[v] = 3 | out[w] = 5, out[u] = 2, out[v] = 4
    So you've converted a tree into an array, and the subarray[in[u] : out[u]]
    is the subtree of u. Now we can use a SegmentTree to query and update on a subtree

  Thank you (/≧▽≦)/
*/

const int maxN = 2e5, maxNE = 5e5, maxE = 3e5, maxQ = 5e5; int n, m, q;
const int inf = maxNE + 1;

int p[maxN];
struct Edge
{
  int u, v, done;
  void read() { scanf("%d %d", &u, &v), done = false; u--, v--; }
};
Edge edges[maxE];

struct Query
{
  int type, value, artificial, queryRoot;
  void read() { scanf("%d %d", &type, &value); value--; }
};
Query queries[maxQ];

int parent[maxNE];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
vector<int> tree[maxNE];
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  // if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
  tree[u].push_back(v), tree[v].push_back(u);
}

void printNode(int u)
{
  printf("%c%d", u < n ? 'v' : 'q', u);
  if (u < n) printf("-%d", p[u]);
}
void printTree(int u = 0, int prv = -1, int depth = 0)
{
  for (int i = 0; i < depth; i++) printf("   ");
  printNode(u); printf("\n");
  for (int v: tree[u])
    if (v != prv)
      printTree(v, u, depth + 1);
}

bool visited[maxNE];
vector<int> roots;
void visit(int u)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: tree[u]) visit(v);
}

vector<vector<int>> eulerTours;
int myEulerTour[maxNE], in[maxNE], out[maxNE];
void buildEulerTour(int u, int prv = -1)
{
  myEulerTour[u] = eulerTours.size() - 1;
  in[u] = eulerTours.back().size();
  eulerTours.back().push_back(u);
  for (int v: tree[u])
    if (v != prv)
      buildEulerTour(v, u);
  out[u] = eulerTours.back().size();
  eulerTours.back().push_back(u);
}

struct MaxData
{
  int value, vertex;
  MaxData operator+(const MaxData &other)
  {
    if (value > other.value)
      return *this;
    return other;
  }
};
const MaxData maxNil = MaxData{0, -1};

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
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
vector<Segtree<MaxData>> segtrees;

int main()
{
  while (scanf("%d %d %d", &n, &m, &q) != EOF)
  {
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < maxNE; i++) tree[i].clear();

    for (int i = 0; i < n; i++)
      scanf("%d", &p[i]);
    for (int i = 0; i < m; i++)
      edges[i].read();

    for (int i = 0; i < q; i++)
    {
      queries[i].read();
      if (queries[i].type == 2)
        edges[queries[i].value].done = true;
    }

    int artificials = n;
    for (int i = 0; i < m; i++)
      if (!edges[i].done)
      {
        Edge &e = edges[i];
        if (root(e.u) == root(e.v)) continue;
        merge(artificials, e.u), merge(artificials, e.v);
        artificials++;
      }

    for (int i = q - 1; i >= 0; i--)
      if (queries[i].type == 2)
      {
        Edge &e = edges[queries[i].value];
        if (root(e.u) == root(e.v)) continue;
        merge(artificials, e.u), merge(artificials, e.v);
        artificials++;
      }
      else
        queries[i].queryRoot = root(queries[i].value);

    memset(visited, false, sizeof(visited));
    roots.clear();
    for (int i = artificials - 1; i >= 0; i--)
      if (!visited[i])
      {
        visit(i);
        roots.push_back(i);
      }

    eulerTours.clear(), segtrees.clear();
    for (int i = 0; i < roots.size(); i++)
    {
      eulerTours.push_back(vector<int>());
      buildEulerTour(roots[i]);
      segtrees.push_back(Segtree<MaxData>(eulerTours.back().size(), maxNil));
      for (int j = 0; j < eulerTours.back().size(); j++)
      {
        int u = eulerTours.back()[j];
        segtrees.back().data[j].value = u < n ? p[u] : -1;
        segtrees.back().data[j].vertex = u < n ? u : -1;
      }
      segtrees.back().build();
    }

    DEBUG
    {
      for (int i = 0; i < roots.size(); i++)
      {
        printTree(roots[i]);
        printf("--------\n");
      }
      for (int i = 0; i < eulerTours.size(); i++)
      {
        for (int u: eulerTours[i])
        {
          printNode(u);
          printf(" ");
        }
        printf("\n-----\n");
      }
    }

    for (int i = 0; i < q; i++)
      if (queries[i].type == 1)
      {
        int u = queries[i].value, met = myEulerTour[u];
        DEBUG printf("\tquery %d %d >= %d\n", u + 1, met, i + 1);

        int highestQuery = queries[i].queryRoot;
        int lo = in[highestQuery], hi = out[highestQuery];
        DEBUG printf("\t\thighestQuery: %d\n", highestQuery);

        MaxData ans = segtrees[met].query(lo, hi);
        printf("%d\n", ans.value);

        if (ans.vertex != -1)
        {
          segtrees[met].update(in[ans.vertex], maxNil);
          segtrees[met].update(out[ans.vertex], maxNil);
        }
      }
  }
  return 0;
}