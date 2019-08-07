#include <bits/stdc++.h>
int segtree[4000000];

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
  int mid = (lo + hi) >> 1;
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
  int mid = (lo + hi) >> 1;
  build(array, lo, mid, 2*i);
  build(array, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int query(int qlo, int qhi, int lo, int hi, int i)
{
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, lo, mid, 2*i) + query(qlo, qhi, mid + 1, hi, 2*i + 1));
}

void update(int array[], int pos, int value, int lo, int hi, int i)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    segtree[i] += value - array[lo];
    array[lo] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  update(array, pos, value, lo, mid, 2*i);
  update(array, pos, value, mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  int n; scanf("%d", &n);
  int array[n]; for (int i = 0; i < n; i ++) scanf("%d", &array[i]);
  build(array, 0, n - 1, 1);
  // printSegTree(0, n - 1, 1, 0);

  char kind;
  while (scanf("%c", &kind) != EOF)
  {
    if (kind == 'Q')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      printf("Sum(%d, %d) = %d\n", lo, hi, query(lo, hi, 0, n - 1, 1));
    }
    else if (kind == 'U')
    {
      int pos, value; scanf("%d %d", &pos, &value); update(array, pos, value, 0, n - 1, 1);
      printf("Update(%d with %d)\n", pos, value);
      // printSegTree(0, n - 1, 1, 0);
    }
  }
  return(0);
}
