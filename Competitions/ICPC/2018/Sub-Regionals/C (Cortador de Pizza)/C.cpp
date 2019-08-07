#include <bits/stdc++.h>
using namespace std;
#define lli long long int

void read(pair<lli, lli> a[], lli s)
{
  for (lli i = 0; i < s; i ++) scanf("%lld %lld", &a[i].first, &a[i].second);
}

lli merge(lli a[], int lo, int hi)
{
  int mid = (lo + hi) / 2, sz = hi - lo + 1;
  lli aux[sz], inv = 0;
  for (int i = lo, j = mid + 1, all = 0; all < sz; all ++)
    if (i > mid || (j <= hi && a[i] > a[j]))
      aux[all] = a[j ++], inv += mid - i + 1;
    else
      aux[all] = a[i ++];

  for (int all = 0; all < sz; all ++) a[lo + all] = aux[all];
  return(inv);
}

lli mergeSort(lli a[], int lo, int hi)
{
  if (lo >= hi) return(0);
  int mid = (lo + hi) / 2; lli inv = 0;
  inv += mergeSort(a, lo, mid);
  inv += mergeSort(a, mid + 1, hi);
  inv += merge(a, lo, hi);
  return(inv);
}

lli inversions(pair<lli, lli> a[], lli s)
{
  sort(a, a+s);
  lli array[s]; for (int i = 0; i < s; i ++) array[i] = a[i].second;
  lli inv = mergeSort(array, 0, s - 1);
  return(inv);
}

int main()
{
  lli x, y; scanf("%lld %lld", &x, &y);
  lli h, v; scanf("%lld %lld", &h, &v);
  pair<lli, lli> horizontal[h], vertical[v]; read(horizontal, h); read(vertical, v);
  lli invH = inversions(horizontal, h), invV = inversions(vertical, v);
  // printf("%lld %lld\n", invH, invV);
  lli ans = (h + 1) * (v + 1) + invH + invV;
  printf("%lld\n", ans);
  return(0);
}