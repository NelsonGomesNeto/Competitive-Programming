#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxX = 1e6 + 1; int n;
pair<int, int> s[maxN];
bool ascents[maxN];
int cnt[maxX + 1];
lli acc[maxX + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt)), acc[0] = 0;

    lli asc = 0;
    for (int i = 0; i < n; i ++)
    {
      s[i] = {-1, maxX}, ascents[i] = false;
      int l; scanf("%d", &l);
      for (int j = 0; j < l; j ++)
      {
        int a; scanf("%d", &a);
        s[i].first = max(s[i].first, a), s[i].second = min(s[i].second, a);
        if (a > s[i].second)
          ascents[i] = true;
      }
      if (ascents[i])
        asc ++;
      else
        cnt[s[i].first] ++;
    }

    for (int i = 0; i <= maxX; i ++)
      acc[i + 1] = acc[i] + cnt[i];

    lli ans = 0;
    for (int i = 0; i < n; i ++)
      if (!ascents[i])
        ans += acc[maxX] - acc[s[i].second + 1];
    ans += 2LL * n * asc - asc*asc;
    printf("%lld\n", ans);
  }
  return 0;
}