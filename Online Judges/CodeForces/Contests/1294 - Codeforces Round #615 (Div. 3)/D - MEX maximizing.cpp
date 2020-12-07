#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 4e5 + 1; int q, x;

int segtree[4*maxX];
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = maxX - 1)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = maxX - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  while (scanf("%d %d", &q, &x) != EOF)
  {
    memset(segtree, 0, sizeof(segtree));
    map<lli, lli> remmap;
    lli now = 0;
    while (q --)
    {
      lli y; scanf("%lld", &y);
      lli rem = y % x;
      if (!remmap.count(rem))
        remmap[rem] = 0;
      remmap[rem] ++;

      lli pos = min((lli)maxX - 1, rem + x*(remmap[rem]-1));

      update(pos, 1);

      DEBUG
      {
        printf("\t%lld %lld - %lld %d\n", y, pos, now, query(0, now));

        for (int i = 0; i <= 10; i ++)
          printf("\t\t%d %d\n", i, query(0, i));
      }

      lli prv = now, nxt = now;
      while (prv < (nxt = query(0, prv)))
        prv = nxt;
      now = prv;
      printf("%lld\n", now);
    }
  }
  return 0;
}
