#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)

void printSegTree(lli segTree[], int lo, int hi, int i)
{
  if (lo >= hi)
  {
    printf("[%d, %d] = %lld\n", lo, hi, segTree[i]);
    return;
  }
  int mid = (lo + hi) / 2;
  printSegTree(segTree, lo, mid, 2*i + 1);
  printSegTree(segTree, mid + 1, hi, 2*i + 2);
  printf("[%d, %d] = %lld\n", lo, hi, segTree[i]);
}

lli build(lli segTree[], int lo, int hi, int i, lli array[], int bitOr)
{
  if (lo >= hi)
  {
    segTree[i] = array[lo];
    return(segTree[i]);
  }
  int mid = (lo + hi) / 2;
  lli left = build(segTree, lo, mid, 2*i + 1, array, 1 - bitOr);
  lli right = build(segTree, mid + 1, hi, 2*i + 2, array, 1 - bitOr);
  if (bitOr) segTree[i] = left | right;
  else segTree[i] = left ^ right;
  return(segTree[i]);
}

lli update(lli segTree[], int lo, int hi, int i, int bitOr, lli value, lli p)
{
  if (hi < p || lo > p || lo >= hi)
  {
    if (lo == p) segTree[i] = value;
    return(segTree[i]);
  }
  int mid = (lo + hi) / 2;
  lli left = update(segTree, lo, mid, 2*i + 1, 1 - bitOr, value, p);
  lli right = update(segTree, mid + 1, hi, 2*i + 2, 1 - bitOr, value, p);
  if (bitOr) segTree[i] = left | right;
  else segTree[i] = left ^ right;
  return(segTree[i]);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int size = pow(2, n);
  lli array[size]; for (int i = 0; i < size; i ++) scanf("%lld", &array[i]);
  lli segTree[3*size]; build(segTree, 0, size - 1, 0, array, n & 1);
  DEBUG {printSegTree(segTree, 0, size - 1, 0); printf("\n");}

  for (int i = 0; i < m; i ++)
  {
    lli p, b; scanf("%lld %lld", &p, &b); array[p - 1] = b;
    update(segTree, 0, size - 1, 0, n & 1, b, p - 1);
    DEBUG {printSegTree(segTree, 0, size - 1, 0); printf("\n");}
    printf("%lld\n", segTree[0]);
  }
  return(0);
}