#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 3e5, maxM = 3e5; int n, m;
int a[maxN], aa[maxN];

bool can(int k)
{
  for (int i = 0; i < n; i ++)
  {
    aa[i] = a[i];
    if (i < n - 1 && m - aa[i] + (i ? aa[i - 1] : 0) <= k) aa[i] = i ? aa[i - 1] : 0;
    if (i && aa[i] < aa[i - 1] && aa[i] + k >= aa[i - 1]) aa[i] = aa[i - 1];
  }
  DEBUG {
    printf("%d\n\t", k);
    for (int i = 0; i < n; i ++) printf("%d%c", aa[i], i < n - 1 ? ' ' : '\n');
  }
  for (int i = 0; i < n - 1; i ++) if (aa[i] > aa[i + 1]) return(false);
  return(true);
}
int binarySearch(int lo = 0, int hi = maxM)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) >> 1;
  if (can(mid)) return(binarySearch(lo, mid));
  return(binarySearch(mid + 1, hi));
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  int ans = binarySearch();
  printf("%d\n", ans);

  return(0);
}
