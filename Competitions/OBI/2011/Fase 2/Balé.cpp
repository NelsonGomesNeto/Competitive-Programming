#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int a[maxN], aux[maxN];

lli merge(int lo, int hi)
{
  lli inversions = 0;
  int mid = (hi + lo) >> 1, size = hi - lo + 1;
  for (int i = lo, j = mid + 1, all = 0; all < size; all ++)
    if (i > mid || (j <= hi && a[j] < a[i]))
    {
      aux[all] = a[j ++];
      inversions += mid - i + 1;
    }
    else if (j > hi || (i <= mid && a[i] < a[j])) aux[all] = a[i ++];

  for (int i = 0; i < size; i ++) a[lo + i] = aux[i];
  return(inversions);
}

lli mergeSort(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return(0);
  int mid = (lo + hi) >> 1;
  lli inversions = mergeSort(lo, mid) + mergeSort(mid + 1, hi);
  inversions += merge(lo, hi);
  return(inversions);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    lli ans = mergeSort();
    // for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
    printf("%lld\n", ans);
  }
  return(0);
}