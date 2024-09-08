#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    pair<int, int> intervals[n];
    for (int i = 0; i < n; i++)
    {
      int t; scanf("%d %d %d", &t, &intervals[i].first, &intervals[i].second);
      intervals[i].first *= 2, intervals[i].second *= 2;
      if (t >= 3) intervals[i].first++;
      if (~t & 1) intervals[i].second--;
    }

    // all closed intervals

    lli ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if ((intervals[i].first >= intervals[j].first && intervals[i].first <= intervals[j].second)
          || (intervals[i].second >= intervals[j].first && intervals[i].second <= intervals[j].second)
          || (intervals[j].first >= intervals[i].first && intervals[j].first <= intervals[i].second)
          || (intervals[j].second >= intervals[i].first && intervals[j].second <= intervals[i].second))
          ans++;
    printf("%lld\n", ans);
  }
  return 0;
}