#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
int a[maxN];
int cnt[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i] %= m;
    }

    for (int i = 0; i < m; i++)
      cnt[i] = 0;

    for (int i = 0; i < n; i++)
      cnt[a[i]]++;

    int ans = cnt[0] != 0;
    for (int i = 1; i < m; i++)
      if (cnt[i])
      {
        int minimum = min(cnt[i], cnt[m - i]);
        int maximum = max(cnt[i], cnt[m - i]);
        ans += 1 + max(0, maximum - (minimum + 1));
        cnt[i] = 0, cnt[m - i] = 0;
      }
    printf("%d\n", ans);

  }
  return 0;
}
