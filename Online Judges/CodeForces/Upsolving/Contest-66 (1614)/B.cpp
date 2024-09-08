#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
pair<int, int> a[maxN];
int x[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i].first);
      a[i].second = i;
    }
    sort(a, a+n);
    reverse(a, a+n);

    lli ans = 0;
    x[0] = 0;
    for (int i = 0, d = 1, turn = 0; i < n; i++)
    {
      ans += 2LL * d * a[i].first;

      if (turn)
      {
        x[1 + a[i].second] = -d;
        d++;
      }
      else
        x[1 + a[i].second] = d;

      turn = !turn;
    }

    printf("%lld\n", ans);
    for (int i = 0; i <= n; i++)
      printf("%d%c", x[i], i < n ? ' ' : '\n');
  }
  return 0;
}
