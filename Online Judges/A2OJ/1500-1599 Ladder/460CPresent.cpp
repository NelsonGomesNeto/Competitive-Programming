#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  (Min, Pos) Segment Tree with Lazy Propagation will work beautifully

  But a Binary Search on the height is enough, since you can test in O(n)
  by summing the amount of movements necessary to reach that height (so, if
  it's bigger that m, try a smaller height)
*/

const int maxN = 1e5; int n, m, w;
const lli inf = 2e9;
lli a[maxN];

struct Ans
{
  lli value; int pos;
  bool operator<(const Ans &a) const { return(value < a.value || (value == a.value && pos < a.pos)); }
  void print() { printf("%lld %d\n", value, pos); }
};
Ans segtree[4*maxN]; lli lazy[4*maxN]; int pending[4*maxN];
void printSegTree(int i = 1, int lo = 0, int hi = n - 1, int depth = 0)
{
  printf("%*c[%d, %d] = (%lld, %d)", depth * 7, ' ', lo, hi, segtree[i].value, segtree[i].pos);
  if (pending[i]) printf(" + (%lld)\n", lazy[i]);
  else printf("\n");
  if (lo >= hi) return;
  int mid = (lo + hi) >> 1;
  printSegTree(2*i, lo, mid, depth + 1);
  printSegTree(2*i + 1, mid + 1, hi, depth + 1);
}
void build(int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo >= hi)
  {
    segtree[i] = {a[lo], lo};
    return;
  }
  int mid = (lo + hi) >> 1;
  build(2*i, lo, mid); build(2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}
void lazyUpdate(int i, int lo, int hi)
{
  if (pending[i])
  {
    segtree[i].value += lazy[i];
    if (lo != hi)
    {
      lazy[2*i] += lazy[i], lazy[2*i + 1] += lazy[i];
      pending[2*i] = pending[2*i + 1] = 1;
    }
    lazy[i] = pending[i] = 0;
  }
}
Ans query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return(Ans({inf, -1}));
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(min(query(qlo, qhi, 2*i, lo, mid), query(qlo, qhi, 2*i + 1, mid + 1, hi)));
}
void updateRange(int qlo, int qhi, lli value, int i = 1, int lo = 0, int hi = n - 1)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i] += value, pending[i] = 1;
    lazyUpdate(i, lo, hi);
    return;
  }
  int mid = (lo + hi) >> 1;
  updateRange(qlo, qhi, value, 2*i, lo, mid); updateRange(qlo, qhi, value, 2*i + 1, mid + 1, hi);
  segtree[i] = min(segtree[2*i], segtree[2*i + 1]);
}

lli movements[maxN];
bool can(lli h)
{
  memset(movements, 0, sizeof(movements));
  lli totalMovements = 0, prevSum = 0;
  for (int i = 0; i < n; i ++)
  {
    lli lostPrevious = (i - w >= 0 ? movements[i - w] : 0);
    lli now = a[i] + prevSum - lostPrevious;
    if (now < h) movements[i] = h - now;
    totalMovements += movements[i], prevSum += movements[i] - lostPrevious;
    if (totalMovements > m) return(false);
  }
  return(true);
}
lli binarySearch(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (can(mid)) return(binarySearch(mid, hi));
  return(binarySearch(lo, mid - 1));
}

int main()
{
  scanf("%d %d %d", &n, &m, &w);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);

  // build();
  // for (int i = 0; i < m; i ++)
  // {
  //   Ans now = query(0, n - 1);
  //   updateRange(now.pos, min(now.pos + w - 1, n - 1), 1);
  // }
  // printf("%lld\n", query(0, n - 1).value);
  printf("%lld\n", binarySearch(1, inf));

  return(0);
}