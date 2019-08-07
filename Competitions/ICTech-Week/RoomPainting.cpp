#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
int shops[maxN];

int binarySearch(int target, int lo = 0, int hi = n - 1)
{
  // printf("%d %d %d\n", lo, hi, target);
  if (lo >= hi) return(shops[lo]);
  int mid = (lo + hi) >> 1;
  if (shops[mid] >= target) return(binarySearch(target, lo, mid));
  return(binarySearch(target, mid + 1, hi));
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%d", &shops[i]);
  sort(shops, shops+n);

  lli ans = 0;
  for (int i = 0, q; i < m; i ++)
  {
    scanf("%d", &q);
    ans += binarySearch(q) - q;
  }
  printf("%lld\n", ans);

  return(0);
}