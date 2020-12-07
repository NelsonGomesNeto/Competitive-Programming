#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

/* Tutorial:
  Using a Segment Tree, we can query LCA(from L to R)

  Run a DFS marking the entry time of each vertex (in[u] = t ++)
  From lo to hi, two nodes can raise the lca the most:
    minx, where in[minx] <= in[from L to R]
    maxx, where in[maxx] >= in[from L to R]
  So, the removed node must be either of them
  You can also query both of them using a Segment Tree
*/

const int maxN = 1e5, maxLog = 20, inf = 1e6; int n, q, lgn;
vector<int> tree[maxN];
int logDP[maxN + 1], level[maxN], ancestor[maxN][maxLog], in[maxN], t;
void dfs(int u = 0)
{
  in[u] = t ++;
  for (int v: tree[u])
  {
    level[v] = level[u] + 1, ancestor[v][0] = u;
    dfs(v);
  }
}
void buildLCA()
{
  level[0] = ancestor[0][0] = 0; dfs();
  for (int i = 1; i < lgn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}

struct Node
{
  int lca, minimum, maximum;
  Node operator+(const Node &s)
  {
    if (lca == -1) return(s);
    if (s.lca == -1) return(*this);
    return(Node({LCA(lca, s.lca), in[minimum] < in[s.minimum] ? minimum : s.minimum, in[maximum] > in[s.maximum] ? maximum : s.maximum}));
  }
  void print()
  {
    printf("lca: %d, minimum: %d, maximum: %d\n", lca, minimum, maximum);
  }
};
Node segtree[4*maxN], nullNode = {-1, -1, -1};
void buildSegtree(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = {lo, lo, lo};
    DEBUG { printf("(%d %d) ", lo + 1, hi + 1); segtree[i].print(); }
    return;
  }
  int mid = (lo + hi) >> 1;
  buildSegtree(2*i, lo, mid), buildSegtree(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
  DEBUG { printf("(%d %d) ", lo + 1, hi + 1); segtree[i].print(); }
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo > qhi || hi < qlo) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  Node ret = query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  // DEBUG { printf("(%d %d) ", lo + 1, hi + 1); ret.print(); }
  return(ret);
}

int main()
{
  for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d %d", &n, &q); lgn = ceil(log2(n));
  for (int i = 1, p; i < n; i ++)
  {
    scanf("%d", &p); p --;
    tree[p].push_back(i);
  }
  buildLCA();
  buildSegtree();
  DEBUG printf("--------------------------------\n");

  while (q --)
  {
    int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
    Node all = query(lo, hi);
    int lca, lca2, removed = all.minimum;

    if (all.minimum == lo) lca = query(all.minimum + 1, hi).lca;
    else if (all.minimum == hi) lca = query(lo, all.minimum - 1).lca;
    else lca = (query(lo, all.minimum - 1) + query(all.minimum + 1, hi)).lca;

    if (all.maximum == lo) lca2 = query(all.maximum + 1, hi).lca;
    else if (all.maximum == hi) lca2 = query(lo, all.maximum - 1).lca;
    else lca2 = (query(lo, all.maximum - 1) + query(all.maximum + 1, hi)).lca;

    if (level[lca2] > level[lca]) lca = lca2, removed = all.maximum;
    printf("%d %d\n", removed + 1, level[lca]);
  }

  return(0);
}