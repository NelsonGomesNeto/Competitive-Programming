#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli b[maxN + 2], a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    int m = n + 2;
    lli totalSum = 0;
    for (int i = 0; i < m; i++)
    {
      scanf("%lld", &b[i]);
      totalSum += b[i];
    }
    sort(b, b+m);

    bool can = false;
    vector<int> biggests = {m - 1, m - 2};
    for (int bigPos: biggests)
    {
      lli big = b[bigPos];
      lli sum = totalSum - big;

      for (int i = 0; i < m; i++)
        if (i != bigPos && sum - b[i] == big)
        {
          can = true;

          DEBUG printf("\tbig: %lld, x: %lld\n", big, b[i]);

          for (int j = 0, jj = 0; j < m; j++)
            if (j != i && j != bigPos)
              a[jj++] = b[j];

          break;
        }
      if (can)
        break;
    }

    if (!can) printf("-1\n");
    else for (int i = 0; i < n; i++) printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
