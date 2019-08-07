#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, m, t;
lli a[maxN], b[maxN], opt[2*maxN];

void read(lli arr[], int size)
{
  for (int i = 0; i < size; i ++)
  {
    scanf("%lld", &arr[i]);
    opt[t ++] = arr[i];
  }
  sort(arr, arr+size);
}

lli getPoints(lli arr[], int size, lli d)
{
  lli lo = upper_bound(arr, arr+size, d) - arr;
  lli hi = size - lo;
  return(lo * 2 + hi * 3); 
}

int main()
{
  scanf("%d", &n); read(a, n);
  scanf("%d", &m); read(b, m);

  lli abest = getPoints(a, n, 0), bbest = getPoints(b, m, 0);
  for (int i = 0; i < t; i ++)
  {
    lli apoints = getPoints(a, n, opt[i]), bpoints = getPoints(b, m, opt[i]);
    if (apoints - bpoints > abest - bbest || (apoints - bpoints == abest - bbest && apoints > abest))
      abest = apoints, bbest = bpoints;
  }
  printf("%lld:%lld\n", abest, bbest);

  return(0);
}