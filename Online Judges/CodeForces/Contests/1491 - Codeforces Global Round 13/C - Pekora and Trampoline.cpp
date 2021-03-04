#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 4 2 2 2 2 2
1 3 2 2 2 1 2
1 2 2 2 1 1 1
1 1 2 1 1 1 1
1 1 1 1 1 1 1
*/

const int maxN = 5e3; int n;
lli s[maxN];
lli pekoras[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &s[i]);
    for (int i = 0; i <= n; i++)
      pekoras[i] = 0;

    for (int i = 0; i < n; i++)
    {
      if (i + s[i] >= n)
      {
        lli prv = s[i];
        s[i] -= i + s[i] - n + 1;
        if (s[i] == 0)
          s[i]++;
        pekoras[n] += prv - s[i];
        pekoras[i] -= prv - s[i];
      }

      pekoras[i] += max(0LL, s[i] - pekoras[i] - 1);

      while (pekoras[i] > 0 && s[i] > 1)
      {
        pekoras[min((lli)n, i + s[i])]++;
        s[i]--;
        pekoras[i]--;
      }

      if (s[i] == 1 && pekoras[i] > 0)
      {
        pekoras[i + 1] += pekoras[i];
        pekoras[i] = 0;
      }
    }
    printf("%lld\n", pekoras[n]);
  }
  return 0;
}
