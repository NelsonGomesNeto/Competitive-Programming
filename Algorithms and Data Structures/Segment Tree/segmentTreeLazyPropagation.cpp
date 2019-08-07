#include <bits/stdc++.h>
#define DEBUG if(0)
int segtree[(int) 4e6], lazy[(int) 4e6], pending[(int) 4e6];

void printSpacing(int depth)
{
  for (int i = 0; i < depth; i ++) printf("   ");
}

void printSegTree(int lo, int hi, int i, int depth)
{
  printSpacing(depth);
  if (lo >= hi)
  {
    printf("[%d,%d] = %d\n", lo, hi, segtree[i]);
    return;
  }
  int mid = (lo + hi) / 2;
  printf("[%d,%d] = %d\n", lo, hi, segtree[i]);
  printSegTree(lo, mid, 2*i, depth + 1);
  printSegTree(mid + 1, hi, 2*i + 1, depth + 1);
}

void build(int array[], int lo, int hi, int i)
{
  if (lo >= hi)
  {
    segtree[i] = array[lo];
    return;
  }
  int mid = (lo + hi) / 2;
  build(array, lo, mid, 2*i);
  build(array, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

void lazyUpdate(int lo, int hi, int i)
{
  if (pending[i])
  {
    segtree[i] = (hi - lo + 1) * lazy[i] + (pending[i] == 2 ? segtree[i] : 0);
    if (lo != hi)
    {
      lazy[2*i] = lazy[i] + (pending[i] - 1) * lazy[2*i];
      lazy[2*i + 1] = lazy[i] + (pending[i] - 1) * lazy[2*i + 1];
      pending[2*i] = pending[2*i] == 1 ? 1 : pending[i];
      pending[2*i + 1] = pending[2*i + 1] == 1 ? 1 : pending[i];
    }
    lazy[i] = 0, pending[i] = 0;
  }
}

int query(int qlo, int qhi, int lo, int hi, int i)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) / 2;
  return(query(qlo, qhi, lo, mid, 2*i) + query(qlo, qhi, mid + 1, hi, 2*i + 1));
}

void updateRange(int array[], int qlo, int qhi, int value, int lo, int hi, int i, int kind)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i] += value, pending[i] = kind;
    lazyUpdate(lo, hi, i);
    return;
  }
  int mid = (lo + hi) / 2;
  updateRange(array, qlo, qhi, value, lo, mid, 2*i, kind);
  updateRange(array, qlo, qhi, value, mid + 1, hi, 2*i + 1, kind);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  int n; scanf("%d", &n);
  int array[n]; for (int i = 0; i < n; i ++) scanf("%d", &array[i]);
  build(array, 0, n - 1, 1); memset(lazy, 0, sizeof(lazy)); memset(pending, 0, sizeof(pending));
  DEBUG printSegTree(0, n - 1, 1, 0);

  char kind;
  while (scanf("\n%c", &kind) != EOF)
  {
    if (kind == 'Q')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      printf("Sum(%d, %d) = %d\n", lo, hi, query(lo, hi, 0, n - 1, 1));
    }
    else if (kind == 'S') // set set (1)
    {
      int lo, hi, add; scanf("%d %d %d", &lo, &hi, &add); updateRange(array, lo, hi, add, 0, n - 1, 1, 1);
      DEBUG printf("SetRange((%d, %d) with %d)\n", lo, hi, add);
      DEBUG printSegTree(0, n - 1, 1, 0);
    }
    else if (kind == 'U') // add update (2)
    {
      int lo, hi, add; scanf("%d %d %d", &lo, &hi, &add); updateRange(array, lo, hi, add, 0, n - 1, 1, 2);
      DEBUG printf("UpdateRange((%d, %d) with %d)\n", lo, hi, add);
      DEBUG printSegTree(0, n - 1, 1, 0);
    }
  }
  return(0);
}
