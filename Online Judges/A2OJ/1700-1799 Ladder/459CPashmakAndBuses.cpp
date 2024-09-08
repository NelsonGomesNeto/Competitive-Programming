#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, k, d;
int ans[maxN][maxN];

bool valid;
int at;
int now[maxN];
void solve(int i = 0)
{
  if (at == n) return;
  if (i == d)
  {
    for (int j = 0; j < d; j ++)
      ans[j][at] = now[j];
    at ++;
    if (at == n) valid = true;
    return;
  }
  for (int j = 1; j <= k && at < n; j ++)
  {
    now[i] = j;
    solve(i + 1);
  }
}

int main()
{
  while (scanf("%d %d %d", &n, &k, &d) != EOF)
  {
    at = 0, valid = false;
    solve();
    if (!valid) printf("-1\n");
    else
      for (int i = 0; i < d; i ++)
        for (int j = 0; j < n; j ++)
          printf("%d%c", ans[i][j], j < n - 1 ? ' ' : '\n');
  }
  return 0;
}