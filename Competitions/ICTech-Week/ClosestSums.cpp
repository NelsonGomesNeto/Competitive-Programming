#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3; int n, t = 1;
int a[maxN];

int binarySearch(bool upperBound, int target, int lo = 0, int hi = n - 1)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi ) >> 1) + upperBound*((lo + hi) & 1);
  if (upperBound)
  {
    if (target >= a[mid]) return(binarySearch(upperBound, target, mid, hi));
    return(binarySearch(upperBound, target, lo, mid - 1));
  }
  else
  {
    if (target <= a[mid]) return(binarySearch(upperBound, target, lo, mid));
    return(binarySearch(upperBound, target, mid + 1, hi));
  }
}

int findClosestSum(int s)
{
  int best = 1e8;
  for (int i = 0; i < n; i ++)
  {
    int lower = binarySearch(false, s - a[i]);
    if (lower == i) lower = lower < n - 1 ? lower + 1 : lower - 1;
    int upper = binarySearch(true, s - a[i]);
    if (upper == i) upper = upper > 0 ? upper - 1 : upper + 1;
    // printf("%d %d %d\n", i, lower, upper);
    if (abs(s - (a[i] + a[lower])) < abs(s - best)) best = a[i] + a[lower];
    if (abs(s - (a[i] + a[upper])) < abs(s - best)) best = a[i] + a[upper];
  }
  return(best);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a+n);
    int m; scanf("%d", &m);
    printf("Case %d:\n", t ++);
    for (int i = 0, s; i < m; i ++)
    {
      scanf("%d", &s);
      int sum = findClosestSum(s);
      printf("Closest sum to %d is %d.\n", s, sum);
    }
  }
  return(0);
}