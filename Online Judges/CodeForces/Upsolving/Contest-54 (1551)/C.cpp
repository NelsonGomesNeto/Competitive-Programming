#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxS = 4e5; int n;
char ss[maxS + 1];
int cnt[maxN][6];
int deltas[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      DEBUG printf("\t%s\n", ss);
      for (int j = 0; j < 6; j++) cnt[i][j] = 0;
      for (int j = 0; ss[j]; j++)
      {
        cnt[i][ss[j] - 'a']++;
        cnt[i][5]++;
      }
    }

    int best = 0;
    for (int i = 0; i < 5; i++)
    {
      int ans = 0;
      for (int j = 0; j < n; j++)
      {
        int aa = cnt[j][i], bb = cnt[j][5] - cnt[j][i];
        deltas[j] = aa - bb;
      }
      sort(deltas, deltas+n, greater<int>());

      int now = 0;
      for (int j = 0; j < n; j++)
      {
        DEBUG printf("\t\t%d %d\n", j, deltas[j]);
        if (deltas[j] > 0) now += deltas[j], ans++;
        else if (now + deltas[j] > 0) now += deltas[j], ans++;
      }
      DEBUG printf("\t%d %d\n", i, now);
      best = max(ans, best);
    }
    printf("%d\n", best);
  }
  return 0;
}
