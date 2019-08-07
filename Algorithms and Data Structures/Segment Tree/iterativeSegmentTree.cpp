#include <bits/stdc++.h>
using namespace std;
const int maxSize = 1e6;
int n, a[maxSize], segtree[2 * maxSize];

// From n to 2*n - 1: put base cases
// From 0 to n - 1: put other nodes

void printSegmentTree()
{
  for (int i = 0; i < 2*n; i ++) printf("%d%c", segtree[i], i < 2*n - 1 ? ' ' : '\n');
}

void build()
{
  for (int i = 0; i < n; i ++) segtree[n + i] = a[i]; // leafs
  for (int i = n - 1; i > 0; i --) segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int query(int lo, int hi)
{
  int value = 0;
  for (lo += n, hi += n + 1; lo < hi; lo >>= 1, hi >>= 1)
    value += (lo & 1 ? segtree[lo ++] : 0) + (hi & 1 ? segtree[-- hi] : 0);
  return(value);
}

void update(int position, int diff)
{
  for (int i = position + n; i; i >>= 1) segtree[i] += diff;
  a[position] += diff;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  build();
  // printSegmentTree();

  char op; int lo, hi, value;
  while (scanf("%c %d %d", &op, &lo, &hi) != EOF)
  {
    if (op == 'Q') printf("Sum(%d, %d) = %d\n", lo, hi, query(lo, hi));
    if (op == 'U') printf("Update(%d with %d)\n", lo, hi), update(lo, hi - a[lo]);
  }

  return(0);
}