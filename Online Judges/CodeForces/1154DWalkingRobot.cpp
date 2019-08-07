#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n, b, a;
bool s[maxN]; int ssum[maxN + 1];

int memo[maxN];
int solve(int i = 0, int battery = b, int accumulator = a)
{
  while (i < n && (battery || accumulator))
  {
    if (s[i] && battery && accumulator < a)
      i ++, battery --, accumulator += 1;
    else if (accumulator)
      i ++, accumulator --;
    else if (battery)
      i ++, battery --;
  }
  return(i);
}

int main()
{
  scanf("%d %d %d", &n, &b, &a);
  for (int i = 0, ss; i < n; i ++) { scanf("%d", &ss); s[i] = ss != 0; ssum[i + 1] = s[i] + ssum[i]; }
  int ans = solve();
  printf("%d\n", ans);
  return(0);
}