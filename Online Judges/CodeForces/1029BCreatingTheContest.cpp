#include <bits/stdc++.h>
using namespace std;
#define lli long long int
lli a[(int) 2e5]; int n;

int solve()
{
  int best = 1, now = 0; lli prevBiggest = -1;
  for (int i = 0; i < n; i ++)
  {
    if (prevBiggest == -1 || a[i] > 2*prevBiggest) now = 0;
    now ++, prevBiggest = a[i];
    best = max(best, now);
  }
  return(best);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  int ans = solve();
  printf("%d\n", ans);
  return(0);
}