#include <bits/stdc++.h>

void build(int segtree[], int array[], int lo, int hi, int i)
{
  if (lo >= hi)
  {
    segtree[i] = array[lo];
    return;
  }
  int mid = (lo + hi) / 2;
  build(segtree, array, lo, mid, 2*i);
  build(segtree, array, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int query(int segtree[], int qlo, int qhi, int lo, int hi, int i)
{
  if (hi < qlo || lo > qhi) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) / 2;
  return(query(segtree, qlo, qhi, lo, mid, 2*i) + query(segtree, qlo, qhi, mid + 1, hi, 2*i + 1));
}

void update(int segtree[], int array[], int pos, int value, int lo, int hi, int i)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    segtree[i] = array[lo] == value ? array[lo] : !array[lo];
    array[lo] = value;
    return;
  }
  int mid = (lo + hi) / 2;
  update(segtree, array, pos, value, lo, mid, 2*i);
  update(segtree, array, pos, value, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  int n; scanf("%d", &n);
  int a[n], aa;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &aa);
    a[i] = aa & 1;
  }
  int segtree[4 * n];
  build(segtree, a, 0, n - 1, 1);

  int q; scanf("%d", &q);
  while (q --)
  {
    int kind, lo, hi; scanf("%d %d %d", &kind, &lo, &hi);
    if (kind == 0) update(segtree, a, lo - 1, hi & 1, 0, n - 1, 1);
    if (kind == 1) printf("%d\n", (hi - lo + 1) - query(segtree, lo - 1, hi - 1, 0, n - 1, 1));
    if (kind == 2) printf("%d\n", query(segtree, lo - 1, hi - 1, 0, n - 1, 1));
  }
  return(0);
}