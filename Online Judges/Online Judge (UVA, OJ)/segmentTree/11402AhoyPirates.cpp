#include <bits/stdc++.h>
#define DEBUG if(0)
int segtree[(int) 4e6], lazy[(int) 4e6]; // stores Buccanneers
char pirates[(int) 1e6 + 1], line[(int) 1e6 + 1];
int da[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2}, {3, 2, 1, 0}};
/* [action][action] relation
now -> past: action
3 -> 1: 2
3 -> 2: 1
3 -> 3: 0

1 -> x: override
2 -> x: override
*/

void build(int lo, int hi, int i)
{
  if (lo >= hi)
  {
    segtree[i] = pirates[lo] == '1', lazy[i] = 0;
    return;
  }
  int mid = (lo + hi) >> 1;
  build(lo, mid, 2*i); build(mid + 1, hi, 2*i + 1);
  segtree[i] = segtree[2*i] + segtree[2*i + 1], lazy[i] = 0;
}

void lazyUpdate(int lo, int hi, int i)
{
  // printf("[%d, %d] l %d - ", lo, hi, lazy[i]);
  if (lazy[i])
  {
    if (lazy[i] == 1) // set Bucanner
      segtree[i] = (hi - lo + 1);
    if (lazy[i] == 2) // set Barbary
      segtree[i] = 0;
    if (lazy[i] == 3) // invert
      segtree[i] = (hi - lo + 1) - segtree[i];
    if (lo != hi)
      lazy[2*i] = da[lazy[i]][lazy[2*i]], lazy[2*i + 1] = da[lazy[i]][lazy[2*i + 1]];
    lazy[i] = 0;
  }
  // printf("%d\n", segtree[i]);
}

void printSpacing(int depth)
{
  for (int i = 0; i < depth; i ++) printf("   ");
}

void printSegTree(int lo, int hi, int i, int depth)
{
  // lazyUpdate(lo, hi, i);
  printSpacing(depth); printf("[%d, %d] = %d (%d)\n", lo, hi, segtree[i], lazy[i]);
  if (lo >= hi) return;
  int mid = (lo + hi) >> 1;
  printSegTree(lo, mid, 2*i, depth + 1);
  printSegTree(mid + 1, hi, 2*i + 1, depth + 1);
}

int query(int qlo, int qhi, int lo, int hi, int i)
{
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[i]);
  int mid = (lo + hi) >> 1;
  return(query(qlo, qhi, lo, mid, 2*i) + query(qlo, qhi, mid + 1, hi, 2*i + 1));
}

void update(int qlo, int qhi, int lo, int hi, int i, int kind)
{
  // printf("[%d, %d] [%d, %d] %d\n", qlo, qhi, lo, hi, kind);
  lazyUpdate(lo, hi, i);
  if (lo > qhi || hi < qlo) return;
  if (lo >= qlo && hi <= qhi)
  {
    lazy[i] = kind;
    lazyUpdate(lo, hi, i);
    return;
  }
  int mid = (lo + hi) >> 1;
  update(qlo, qhi, lo, mid, 2*i, kind); update(qlo, qhi, mid + 1, hi, 2*i + 1, kind);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  int t; scanf("%d", &t);
  for (int r = 1; r <= t; r ++)
  {
    pirates[0] = '\0';
    int m, t, n = 0; scanf("%d", &m);
    while (m --)
    {
      scanf("%d", &t);
      scanf("\n%s", line);
      while (t --) for (int i = 0; line[i]; i ++, n ++) pirates[n] = line[i];
    }
    pirates[n] = '\0';
    build(0, n - 1, 1);

    printf("Case %d:\n", r);
    int q; scanf("%d", &q);
    char op; int lo, hi, qq = 1;
    for (int qi = 1; qi <= q; qi ++)
    {
      scanf("\n%c %d %d", &op, &lo, &hi); // kind = op == 'F' ? 1 : op == 'E' ? 2 : 3;
      if (op == 'F') update(lo, hi, 0, n - 1, 1, 1); // set Buccanneer
      if (op == 'E') update(lo, hi, 0, n - 1, 1, 2); // set Barbary
      if (op == 'I') update(lo, hi, 0, n - 1, 1, 3); // inverse pirates
      if (op == 'S') printf("Q%d: %d\n", qq ++, query(lo, hi, 0, n - 1, 1));
      // DEBUG printSegTree(0, n - 1, 1, 0);
    }
  }
  return(0);
}