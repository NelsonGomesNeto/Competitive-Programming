#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxM = 1e6; int n, m;
lli v[maxN], vCopy[maxN], newPosition[maxN], aux[maxN];
bool has[maxM];

lli merge(int lo, int mid, int hi)
{
  int sz = hi - lo + 1; lli inversions = 0;
  for (int i = lo, j = mid + 1, a = 0; a < sz; a ++)
    if (i <= mid && (j > hi || v[i] <= v[j]))
      aux[a] = v[i ++];
    else
      aux[a] = v[j ++], inversions += mid - i + 1;
  for (int a = 0; a < sz; a ++)
    v[lo + a] = aux[a];
  return(inversions);
}

lli mergeSort(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return(0);
  int mid = (lo + hi) >> 1;
  lli inversions = mergeSort(lo, mid);
  inversions += mergeSort(mid + 1, hi);
  inversions += merge(lo, mid, hi);
  return(inversions);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &v[i]);

  // lli inv = 0;
  // for (int i = 0; i < n; i ++)
  //   for (int j = i + 1; j < n; j ++)
  //     inv += v[i] > v[j];

  memcpy(vCopy, v, sizeof(v));
  lli inversions = mergeSort();
  // printf("%lld -- %lld\n", inv, inversions);

  for (int i = 0; i < n; i ++)
    for (int j = 0;; j ++)
    {
      int pos = (vCopy[i] + j * inversions) % m;
      if (!has[pos])
      {
        has[pos] = true, newPosition[i] = pos;
        break;
      }
    }
  for (int i = 0; i < n; i ++)
    printf("%lld\n", newPosition[i]);

  return(0);
}