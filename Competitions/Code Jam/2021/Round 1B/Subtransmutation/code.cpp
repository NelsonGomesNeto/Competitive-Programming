#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20, maxX = 1e5; int n;
int u[maxN + 1], a, b;

lli curr[maxX + 1];
bool valid(int start = 1)
{
  for (int i = start; i <= n; i++)
    if (curr[i] < u[i])
      return false;
  return true;
}

bool can(int base)
{
  if (base < 0) return false;
  memset(curr, 0, sizeof(curr));

  curr[base] = 1;

  for (int i = base; i >= 1; i--)
  {
    if (i <= n && curr[i] < u[i]) return false;
    lli delta = i > n ? curr[i] : curr[i] - u[i];
    int l = i - a, r = i - b;
    if (l >= 1) curr[l] += delta;
    if (r >= 1) curr[r] += delta;
    curr[i] -= delta;
  }

  return valid();
}

int main()
{
  int t;
  while (~scanf("%d", &t))
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %d", &n, &a, &b);
      for (int i = 1; i <= n; i++)
        scanf("%d", &u[i]);

      int lo = 1, hi = a * 100, dk = 10;
      while (lo < hi)
      {
        int mid = (lo + hi) >> 1;
        bool valid = false;
        for (int i = -dk; i <= dk && !valid; i++)
          valid = can(mid + i);
        if (valid) hi = mid;
        else lo = mid + 1;
      }

      int ans = -1;
      for (int i = lo + dk; i >= lo - dk; i--)
        if (can(i))
          ans = i;

      printf("Case #%d: ", tt);
      if (ans != -1) printf("%d\n", ans);
      else printf("IMPOSSIBLE\n");
      fflush(stdout);
    }
  return 0;
}