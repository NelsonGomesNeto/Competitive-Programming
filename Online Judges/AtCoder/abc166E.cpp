#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
map<int, int> cnt[2];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    cnt[0].clear(), cnt[1].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      lli b = a[i] + (i + 1), c = (i + 1) - a[i];
      if (!cnt[0].count(b)) cnt[0][b] = 0;
      cnt[0][b]++;
      if (!cnt[1].count(c)) cnt[1][c] = 0;
      cnt[1][c]++;
    }

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      lli b = a[i] + (i + 1);
      ans += cnt[1].count(b) ? cnt[1][b] : 0;
    }
    printf("%lld\n", ans);
  }
  return 0;
}