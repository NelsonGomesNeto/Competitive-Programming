#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1000; int n, m, d;
int c[maxN], pos[maxN], ans[maxN];

int main()
{
  while (scanf("%d %d %d", &n, &m, &d) != EOF)
  {
    int sum = 0;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d", &c[i]);
      sum += c[i];
    }

    bool can = false;
    for (int i = 0, at = -1; i < m; i ++)
    {
      sum -= c[i];
      for (int j = d; j >= 1; j --)
        if (n - (at + j + c[i]) >= sum)
        {
          pos[i] = at + j;
          at += j + c[i] - 1;
          DEBUG printf("%d %d %d\n", i, pos[i], at);
          break;
        }
      if (at + d >= n)
        can = true;
    }

    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < m; i ++)
      for (int j = 0; j < c[i]; j ++)
        ans[pos[i] + j] = i + 1;
    if (can)
    {
      printf("YES\n");
      for (int i = 0; i < n; i ++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
    else printf("NO\n");
  }
  return 0;
}
