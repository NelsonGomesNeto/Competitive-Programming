#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int

lli merge(int a[], int lo, int hi)
{
  int aSize = hi - lo + 1, mid = (lo + hi) / 2;
  // printf("%d %d %d %d\n", lo, hi, aSize, mid);
  int aux[aSize]; lli inversions = 0;
  for (int i = lo, j = mid + 1, all = 0; all < aSize; all ++)
    if (i > mid || (j <= hi && a[i] > a[j]))
      aux[all] = a[j ++], inversions += mid - i + 1;
    else
      aux[all] = a[i ++];
  for (int i = 0; i < aSize; i ++) a[i + lo] = aux[i];
  return(inversions);
}

lli mergeSort(int a[], int lo, int hi)
{
  if (lo >= hi) return(0);
  int mid = (lo + hi) / 2;
  lli inversions = 0;
  inversions += mergeSort(a, lo, mid);
  inversions += mergeSort(a, mid + 1, hi);
  inversions += merge(a, lo, hi);
  return(inversions);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    lli inversions = mergeSort(a, 0, n - 1);
    printf("%lld\n", inversions);
    DEBUG for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  }
  return(0);
}