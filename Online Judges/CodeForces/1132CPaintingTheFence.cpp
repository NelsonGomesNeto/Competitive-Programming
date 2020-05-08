#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n, q;
pair<int, int> painters[maxN];
int cnt[maxN], in[maxN], out[maxN];

int acc[maxN + 1], acc2[maxN + 1];
int subPainter(int i)
{
  return acc[painters[i].second + 1] - acc[painters[i].first];
}
int subPainters(int i, int j)
{
  int lo = max(painters[i].first, painters[j].first), hi = min(painters[i].second, painters[j].second);
  if (lo > hi) return 0;
  return acc2[hi + 1] - acc2[lo];
}

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    memset(cnt, 0, sizeof(cnt)), memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
    for (int i = 0; i < q; i++)
    {
      scanf("%d %d", &painters[i].first, &painters[i].second);
      painters[i].first--, painters[i].second--;
      in[painters[i].first]++, out[painters[i].second]++;
    }

    int total = 0;
    for (int i = 0, now = 0; i < n; i++)
    {
      now += in[i];
      DEBUG printf("\t%d %d\n", i, now);
      total += now > 0;
      cnt[i] = now;
      now -= out[i];
    }

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + (cnt[i] == 1);
    for (int i = 0; i < n; i++)
      acc2[i + 1] = acc2[i] + (cnt[i] == 2);

    DEBUG
      for (int i = 0; i <= n; i++)
        printf("%d%c", acc[i], i < n ? ' ' : '\n');

    int ans = 0;
    for (int i = 0; i < q; i++)
      for (int j = i + 1; j < q; j++)
      {
        DEBUG printf("%d %d - %d\n", i, j, total - subPainter(i) - subPainter(j) - subPainters(i, j));
        ans = max(ans, total - subPainter(i) - subPainter(j) - subPainters(i, j));
      }
    printf("%d\n", ans);
  }
  return 0;
}