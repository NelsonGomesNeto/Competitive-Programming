#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n; lli z;
lli x[maxN];

bool can(int guess)
{
  for (int i = 0; i < guess; i ++)
    if (abs(x[n - i - 1] - x[guess - i - 1]) < z) // This is the optimal making of pairs
      return(false);
  return(true);
}

int binarySearch(int lo, int hi)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (can(mid)) return(binarySearch(mid, hi));
  return(binarySearch(lo, mid - 1));
}

int main()
{
  scanf("%d %lld", &n, &z);
  for (int i = 0; i < n; i ++) scanf("%lld", &x[i]);
  sort(x, x+n);

  int ans = binarySearch(0, n >> 1);
  printf("%d\n", ans);

  return(0);
}
