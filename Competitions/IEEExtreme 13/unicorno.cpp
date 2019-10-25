#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m, s;

struct Interval
{
  int lo, hi;
  void read() { scanf("%d %d", &lo, &hi); }
};
Interval broken[maxN];
struct Power
{
  lli cost; Interval interval; lli covered;
  void read() { interval.read(); scanf("%lld", &cost); }
  bool operator<(const Power &other) const { return covered*cost > other.covered*other.cost; }
};
Power powers[maxN];

int segtree[4*(maxN + 1)], pending[4*(maxN + 1)], lazy[4*(maxN + 1)];
void lazyUpdate(int i, int lo, int hi)
{
  if (pending[i])
  {
    segtree[i] = lazy[i]*(hi - lo + 1);
    if (lo != hi)
      pending[2*i] = pending[2*i + 1] = pending[i], lazy[2*i] = lazy[2*i + 1] = lazy[i];
    pending[i] = lazy[i] = 0;
  }
}
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = s)
{
  lazyUpdate(i, lo, hi);
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int qlo, int qhi, int value, int i = 1, int lo = 0, int hi = s)
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
  scanf("%d %d %d", &n, &m, &s);
  for (int i = 0; i < n; i ++)
  {
    broken[i].read();
    update(broken[i].lo, broken[i].hi, 1);
  }
  for (int i = 0; i < m; i ++)
  {
    powers[i].read();
    powers[i].covered = query(powers[i].interval.lo, powers[i].interval.hi);
  }
  sort(powers, powers+m);

  lli ans = 0;
  for (int i = 0; i < m; i ++)
  {
    if (query(powers[i].interval.lo, powers[i].interval.hi))
    {
      ans += powers[i].cost;
      update(powers[i].interval.lo, powers[i].interval.hi, 0);
    }
  }
  printf("%lld\n", ans);

  return 0;
}