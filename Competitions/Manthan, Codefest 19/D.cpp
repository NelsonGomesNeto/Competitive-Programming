#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
const lli inf = 1e12;
lli p[maxN]; int a[maxN];

struct Node
{
  lli minp; int maxpos;
  Node operator+(const Node& other)
  {
    if (minp < other.minp) return *this;
    else if (other.minp < minp) return other;
    return Node({minp, max(maxpos, other.maxpos)});
  }
  void print()
  {
    printf("%lld %d\n", minp, maxpos);
  }
};
Node segtree[4*maxN], nullNode = Node({inf, maxN}); lli lazy[4*maxN]; int pending[4*maxN];
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = Node({p[lo], lo});
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
void lazyUpdate(int i, int lo, int hi)
{
  if (pending[i])
  {
    segtree[i].minp += lazy[i];
    if (lo != hi)
      pending[2*i] = pending[2*i + 1] = 1, lazy[2*i] += lazy[i], lazy[2*i + 1] += lazy[i];
    pending[i] = lazy[i] = 0;
  }
}
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  lazyUpdate(i, lo, hi);
  if (hi < qlo || lo > qhi) return nullNode;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int qlo, int qhi, lli value, int i = 1, int lo = 0, int hi = n - 1)
{
  lazyUpdate(i, lo, hi);
  if (hi < qlo || lo > qhi) return;
  if (lo >= qlo && hi <= qhi)
  {
    pending[i] = 1, lazy[i] = value;
    lazyUpdate(i, lo, hi);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, value, 2*i, lo, mid), update(qlo, qhi, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &p[i]);
  build();

  for (int i = 1; i <= n; i ++)
  {
    Node ans = query(0, n - 1);
    a[ans.maxpos] = i;
    update(ans.maxpos, ans.maxpos, inf);
    if (ans.maxpos < n - 1)
      update(ans.maxpos + 1, n - 1, -i);
  }

  for (int i = 0; i < n; i ++)
    printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');

  return(0);
}
