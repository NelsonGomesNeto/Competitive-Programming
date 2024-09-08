#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m; scanf("%d %d", &n, &m);
    lli capacity[n]; for (int i = 0; i < n; i ++) scanf("%lld", &capacity[i]);
    lli now[n + 1]; memset(now, 0, sizeof(now));
    for (int i = 0; i < m; i ++)
    {
      lli x, y; scanf("%lld %lld", &x, &y); x --;
      now[x] += y;
    }
    for (int i = 0; i < n; i ++)
    {
      now[i + 1] += now[i] > capacity[i] ? now[i] - capacity[i] : 0;
      now[i] = min(now[i], capacity[i]);
    }

    printf("%lld\n", now[n]);
    for (int i = 0; i < n; i ++) printf("%lld%c", now[i], i < n - 1 ? ' ' : '\n');
  }
  return(0);
}
