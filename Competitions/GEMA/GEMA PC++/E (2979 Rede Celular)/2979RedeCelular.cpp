#include <bits/stdc++.h>
using namespace std;
 
const int maxN = 1e5; int n, m;
int a[maxN], b[maxN];
 
int binarySearch(int target, bool upper)
{
  int lo = 0, hi = m - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upper) >> 1;
    if (upper)
    {
      if (b[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (b[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}
 
int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);
  for (int i = 0; i < m; i ++)
    scanf("%d", &b[i]);
 
  int ans = 0;
  for (int i = 0; i < n; i ++)
  {
    int pos = binarySearch(a[i], false);
    int cl = abs(b[pos] - a[i]);
    pos = binarySearch(a[i], true);
    int cr = abs(a[i] - b[pos]);
    ans = max(ans, min(cl, cr));
  }
  printf("%d\n", ans);
 
  return 0;
}