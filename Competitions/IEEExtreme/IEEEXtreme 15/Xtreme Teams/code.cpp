#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3, maxM = 12; int n, m;
int masks[maxN], fullMask;
bitset<maxN> has[maxM], notHas[maxM], allSet;
char s[maxN + 1];
pair<int, int> memo[1 << maxM];

int main()
{
  allSet = 0;
  allSet.flip();

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int j = 0; j < m; j++) has[j] = notHas[j] = 0;
    fill(memo, memo+(1<<m), make_pair(-1, -1));
    fullMask = (1 << m) - 1;

    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s);
      masks[i] = 0;
      for (int j = 0; j < m; j++)
        if (s[j] == 'y')
          masks[i] |= (1 << j);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      if (i)
        for (int j = i + 1; j < n; j++)
        {
          int missing = fullMask & ~(masks[i] | masks[j]);

          if (memo[missing].first == i)
          {
            ans += memo[missing].second;
            continue;
          }

          if (missing == 0)
          {
            ans += i;
            continue;
          }

          // if (__builtin_popcount(missing) < (m << 1))
          // {
          //   bitset<maxN> curr = allSet;
          //   for (int bit = 0; bit < m; bit++)
          //     if (missing & (1 << bit))
          //       curr &= has[bit];

          //   ans += memo[missing].second = curr.count();
          //   memo[missing].first = i;
          // }
          // else
          if (i < 100)
          {
            int total = 0;
            for (int k = 0; k < i; k++)
              total += (missing == (masks[k] & missing));

            ans += memo[missing].second = total;
            memo[missing].first = i;
          }
          else
          {
            bitset<maxN> curr = 0;
            for (int bit = 0; bit < m; bit++)
              if (missing & (1 << bit))
                curr |= notHas[bit];

            ans += memo[missing].second = (i - curr.count());
            memo[missing].first = i;
          }
        }

      for (int j = 0; j < m; j++)
        if (masks[i] & (1 << j))
          has[j][i] = true;
        else
          notHas[j][i] = true;
    }
    printf("%d\n", ans);
  }
  return 0;
}