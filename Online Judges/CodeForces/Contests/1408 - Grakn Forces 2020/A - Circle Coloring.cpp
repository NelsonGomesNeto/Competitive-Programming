#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
int a[maxN], b[maxN], c[maxN], ans[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++) scanf("%d", &a[i]);
      for (int i = 0; i < n; i++) scanf("%d", &b[i]);
      for (int i = 0; i < n; i++) scanf("%d", &c[i]);

      for (int i = 0; i < n; i++)
      {
        ans[i] = a[i];
        if ((i && ans[i] == ans[i - 1]) || (i == n - 1 && ans[i] == ans[0]))
          ans[i] = b[i];
        if ((i && ans[i] == ans[i - 1]) || (i == n - 1 && ans[i] == ans[0]))
          ans[i] = c[i];
      }

      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}
