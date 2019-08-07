#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n; lli k;
lli a[maxN], accSum[maxN + 1];

int binarySearch(int lo, int hi, int id)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1);
  int b = id - mid + 1; lli sum = accSum[id + 1] - accSum[mid];
  if (b*a[id] - sum <= k) return(binarySearch(lo, mid, id));
  return(binarySearch(mid + 1, hi, id));
}

int main()
{
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  sort(a, a+n);
  for (int i = 0; i < n; i ++) accSum[i + 1] = accSum[i] + a[i];

  int start = 0; while (start < n && a[start] == 0) start ++;
  int best = start * (a[0] == 0); lli bestN = 0;

  for (int i = start; i < n; i ++)
  {
    while (i < n - 1 && a[i] == a[i + 1]) i ++;
    int total = i - binarySearch(0, i, i) + 1;
    if (total > best) best = total, bestN = a[i];
  }
  printf("%d %lld\n", best, bestN);

  return(0);
}