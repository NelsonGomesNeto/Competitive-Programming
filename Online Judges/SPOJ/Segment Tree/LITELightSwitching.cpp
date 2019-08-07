#include <bits/stdc++.h>
int segtree[(int) 4e5], lazy[(int) 4e5];

void lazyUpdate(int lo, int hi, int i)
{
  if (lazy[i] & 1)
  {
    segtree[i] = (hi - lo + 1) - segtree[i];
    if (lo != hi) lazy[2*i] ++, lazy[2*i + 1] ++;
    lazy[i] = 0;
  }
}

void update(int qlo, int qhi, int lo, int hi, int i = 1)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i] ++;
    lazyUpdate(lo, hi, i);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, lo, mid, 2*i);
  update(qlo, qhi, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int query(int qlo, int qhi, int lo, int hi, int i = 1)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, lo, mid, 2*i) + query(qlo, qhi, mid + 1, hi, 2*i + 1));
}

int main()
{
  memset(segtree, 0, sizeof(segtree)); memset(lazy, 0, sizeof(lazy));
  int n, m; scanf("%d %d", &n, &m);

  while (m --)
  {
    int op, lo, hi; scanf("%d %d %d", &op, &lo, &hi); lo --, hi --;
    if (op) printf("%d\n", query(lo, hi, 0, n - 1));
    else update(lo, hi, 0, n - 1);
  }
  return(0);
}
