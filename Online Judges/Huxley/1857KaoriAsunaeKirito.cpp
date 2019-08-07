#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];
int t, in[maxN], out[maxN]; lli tour[2*maxN], value[maxN];
void dfs(int u = 0, int prv = -1)
{
  in[u] = t; tour[t ++] = value[u];
  for (int v: tree[u])
    if (v != prv)
      dfs(v, u);
  out[u] = t; tour[t ++] = value[u];
}

struct Node
{
  int cnt[32];
  Node operator+(const Node &node)
  {
    Node temp;
    for (int i = 0; i < 32; i ++)
      temp.cnt[i] = cnt[i] + node.cnt[i];
    return(temp);
  }
  void operator^=(const Node &node)
  {
    for (int i = 0; i < 32; i ++) cnt[i] ^= node.cnt[i];
  }
  void setNumber(lli number)
  {
    for (int i = 0; number; i ++, number >>= 1)
      cnt[i] = number & 1;
  }
  void update(Node &node, int size)
  {
    for (int i = 0; i < 32; i ++)
      if (node.cnt[i])
        cnt[i] = size - cnt[i];
  }
  lli value()
  {
    lli v = 0; int nxt = 0;
    for (int i = 0; i < 32; i ++)
    {
      // printf("|%d|", cnt[i]);
      v += (nxt + cnt[i]) & 1 ? 1LL << i : 0;
      nxt = (nxt + cnt[i]) >> 1;
    }
    // printf("\n");
    return(v);
  }
};
Node segtree[4*2*maxN], lazy[4*2*maxN], nullNode; bool pending[4*2*maxN];
void build(int i = 1, int lo = 0, int hi = t - 1)
{
  if (lo == hi)
  {
    segtree[i].setNumber(tour[lo]);
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
  // segtree[i].value();
}
void lazyUpdate(int i, int lo, int hi)
{
  if (pending[i])
  {
    segtree[i].update(lazy[i], hi - lo + 1);
    if (lo != hi)
    {
      lazy[2*i] ^= lazy[i], lazy[2*i + 1] ^= lazy[i];
      pending[2*i] = pending[2*i + 1] = true;
    }
    lazy[i] = nullNode, pending[i] = false;
  }
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = t - 1)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return(nullNode);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int qlo, int qhi, lli x, int i = 1, int lo = 0, int hi = t - 1)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i].setNumber(x), pending[i] = true;
    lazyUpdate(i, lo, hi);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, x, 2*i, lo, mid), update(qlo, qhi, x, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  scanf("%d", &n);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  for (int i = 0; i < n; i ++) scanf("%lld", &value[i]);
  dfs();
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    int op; scanf("%d", &op);
    if (op == 2)
    {
      int u; scanf("%d", &u); u --;
      printf("%lld\n", query(in[u], out[u]).value() >> 1);
    }
    else
    {
      int u; lli x; scanf("%d %lld", &u, &x); u --;
      update(in[u], out[u], x);
    }
  }

  return(0);
}