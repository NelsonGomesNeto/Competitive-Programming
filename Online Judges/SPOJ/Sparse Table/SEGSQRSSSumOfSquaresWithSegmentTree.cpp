#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
// 0 - normal, 1 - power
lli segtree[2][(int) 4e6], lazy[(int) 4e6]; int needsUpdate[(int) 4e6];
int n, q;

void printSpacing(int depth)
{
  for (int i = 0; i < depth; i ++) printf("   ");
}

void lazyUpdate(int i, int lo, int hi);

void printSegTree(int lo, int hi, int i, int seg, int depth)
{
  printSpacing(depth); printf("%d ", needsUpdate[i]);
  // lazyUpdate(i, lo, hi);
  printf("[%d, %d] = %lld\n", lo, hi, segtree[seg][i]);
  if (lo >= hi) return;
  int mid = (lo + hi) / 2;
  printSegTree(lo, mid, 2*i, seg, depth + 1);
  printSegTree(mid + 1, hi, 2*i + 1, seg, depth + 1);
}

void build(lli array[], int lo, int hi, int i, int seg)
{
  if (lo >= hi)
  {
    segtree[seg][i] = array[lo];
    return;
  }
  int mid = (lo + hi) / 2;
  build(array, lo, mid, 2*i, seg);
  build(array, mid + 1, hi, 2*i + 1, seg);
  segtree[seg][i] = segtree[seg][2*i] + segtree[seg][2*i + 1];
}

void lazyUpdate(int i, int lo, int hi)
{
  if (needsUpdate[i])
  {
    if (needsUpdate[i] == 1) // set update
      segtree[1][i] = (hi - lo + 1) * lazy[i] * lazy[i], segtree[0][i] = (hi - lo + 1) * lazy[i];
    else // add update
    {
      segtree[1][i] += (hi - lo + 1) * lazy[i] * lazy[i] + 2 * lazy[i] * segtree[0][i];
      segtree[0][i] += (hi - lo + 1) * lazy[i];
    }
    if (lo != hi)
    {
      lazy[2*i] = lazy[i] + (needsUpdate[i]-1) * lazy[2*i], lazy[2*i + 1] = lazy[i] + (needsUpdate[i]-1) * lazy[2*i + 1];
      needsUpdate[2*i] = needsUpdate[2*i + 1] = needsUpdate[2*i] == 1 ? 1 : needsUpdate[i];
    }
    lazy[i] = needsUpdate[i] = 0;
  }
}

lli query(int qlo, int qhi, int lo, int hi, int i, int seg)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[seg][i]);
  int mid = (lo + hi) / 2;
  return(query(qlo, qhi, lo, mid, 2*i, seg) + query(qlo, qhi, mid + 1, hi, 2*i + 1, seg));
}

void updateRange(int qlo, int qhi, lli x, int lo, int hi, int i, int kind)
{
  lazyUpdate(i, lo, hi);
  if (lo > qhi || hi < qlo) return;
  // printf("%d %d %d %d %d\n", lo, hi, qlo, qhi, lo >= qlo && hi <= qhi);
  if (lo >= qlo && hi <= qhi)
  {
    if (!kind) segtree[0][i] = (hi - lo + 1) * x, segtree[1][i] = (hi - lo + 1) * x * x; // set update
    else // add update
    {
      segtree[1][i] += (hi - lo + 1) * x * x + 2 * x * segtree[0][i];
      segtree[0][i] += (hi - lo + 1) * x;
    }
    if (lo != hi)
    {
      lazy[2*i] = x + kind * lazy[2*i], lazy[2*i + 1] = x + kind * lazy[2*i + 1];
      needsUpdate[2*i] = needsUpdate[2*i + 1] = needsUpdate[2*i] == 1 ? 1 : (kind + 1);
    }
    return;
  }
  int mid = (lo + hi) / 2;
  updateRange(qlo, qhi, x, lo, mid, 2*i, kind);
  updateRange(qlo, qhi, x, mid + 1, hi, 2*i + 1, kind);
  segtree[0][i] = segtree[0][2*i] + segtree[0][2*i + 1];
  segtree[1][i] = segtree[1][2*i] + segtree[1][2*i + 1];
}

int main()
{
  int t; scanf("%d", &t);
  for (int r = 1; r <= t; r ++)
  {
    scanf("%d %d", &n, &q); memset(needsUpdate, 0, sizeof(needsUpdate)); memset(lazy, 0, sizeof(lazy));
    lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
    lli sq[n]; for (int i = 0; i < n; i ++) sq[i] = a[i] * a[i];
    build(a, 0, n - 1, 1, 0), build(sq, 0, n - 1, 1, 1);
    DEBUG { printSegTree(0, n - 1, 1, 0, 0); printSegTree(0, n - 1, 1, 1, 0); }

    printf("Case %d:\n", r);
    while (q --)
    {
      int kind, st, nd; lli x; scanf("%d", &kind);
      if (kind < 2)
      {
        scanf("%d %d %lld", &st, &nd, &x); // set range
        updateRange(st - 1, nd - 1, x, 0, n - 1, 1, kind);
        DEBUG printf("%s update (%d, %d) with %lld\n", kind == 1 ? "add" : "set", st, nd, x);
        DEBUG { printSegTree(0, n - 1, 1, 0, 0); printSegTree(0, n - 1, 1, 1, 0); }
      }
      else if (kind == 2)
      {
        scanf("%d %d", &st, &nd);
        printf("%lld\n", query(st - 1, nd - 1, 0, n - 1, 1, 1));
      }
    }
    DEBUG { printSegTree(0, n - 1, 1, 0, 0); printSegTree(0, n - 1, 1, 1, 0); printf("\n"); }
  }
  return(0);
}
