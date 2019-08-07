#include <bits/stdc++.h>
#define lli long long int
lli mod = 1e9 + 7;

lli run(lli x, lli y, lli i, lli n, lli line[][3], lli k)
{
  //printf("%lld %lld %lld\n", x, y, i);
  if (x == k && !y) return(1);
  if (x >= k) return(0);
  if (x > line[i][1] && i + 1 < n) i ++;
  if (x >= line[i][0] && x <= line[i][1] && y > line[i][2]) return(0);

  lli paths = 0;
  if (y) paths = (paths + run(x + 1, y - 1, i, n, line, k)) % mod;
  paths = (paths + run(x + 1, y, i, n, line, k)) % mod;
  paths = (paths + run(x + 1, y + 1, i, n, line, k)) % mod;

  return(paths);
}

int main()
{
  lli n, k; scanf("%lld %lld", &n, &k);
  lli line[n][3];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < 3; j ++)
      scanf("%lld", &line[i][j]);

  lli ans = run(0, 0, 0, n, line, k);
  printf("%lld\n", ans);

  return(0);
}