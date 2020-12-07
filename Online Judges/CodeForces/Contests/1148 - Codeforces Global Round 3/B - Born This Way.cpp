#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5, maxM = 2e5; int n, m, k; lli ta, tb;
lli a[maxN], b[maxM];

int binarySearch(lli target, int lo = 0, int hi = m - 1)
{
  if (lo >= hi) return(target > b[lo] ? lo + 1 : lo);
  int mid = (lo + hi) >> 1;
  if (target > b[mid]) return(binarySearch(target, mid + 1, hi));
  return(binarySearch(target, lo, mid));
}

int main()
{
  scanf("%d %d %lld %lld %d", &n, &m, &ta, &tb, &k);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  for (int i = 0; i < m; i ++) scanf("%lld", &b[i]);

  lli ans = 0;
  for (int i = 0, end = min(n - 1, k); i <= k; i ++)
  {
    // int pos = upper_bound(b, b+m, a[i] + ta - 1) - b;
    int pos = binarySearch(a[i] + ta);
    pos += k - i;
    if (pos >= m) ans = -1;
    if (pos < m && ans != -1) ans = max(ans, b[pos] + tb);
  }
  printf("%lld\n", k >= n || k >= m ? -1 : ans);

  return(0);
}
